// Source/AudioStreamClient/WebSocketClient.cpp
#include "WebSocketClient.h"
#include "WebSocketsModule.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"

FWebSocketClient::FWebSocketClient() :
    WebSocket(nullptr),
    bIsConnected(false)
{
}

FWebSocketClient::~FWebSocketClient()
{
	Disconnect();
}

void FWebSocketClient::Connect(const FString& Url)
{
	if (!FModuleManager::Get().IsModuleLoaded(TEXT("WebSockets")))
	{
		FModuleManager::Get().LoadModule(TEXT("WebSockets"));
	}

	if (WebSocket.IsValid())
	{
		Disconnect();
	}

	WebSocket = FWebSocketsModule::Get().CreateWebSocket();

    if(WebSocket.IsValid())
    {
        WebSocket->OnConnected().AddLambda([this](){
            bIsConnected = true;
            UE_LOG(LogTemp, Log, TEXT("Websocket Connected!"));
            });

        WebSocket->OnMessage().AddLambda([this](const FString& Message) {
                OnMessage.ExecuteIfBound(Message);
            });

        WebSocket->OnConnectionError().AddLambda([this](const FString& Error) {
                bIsConnected = false;
                OnError.ExecuteIfBound(Error);
                UE_LOG(LogTemp, Error, TEXT("Websocket Connection Error: %s"), *Error);
             });

        WebSocket->OnClosed().AddLambda([this](int32 StatusCode, const FString& Reason, bool bWasClean){
            bIsConnected = false;
            UE_LOG(LogTemp, Log, TEXT("Websocket Closed %s, Reason: %s, Clean: %d"), *FString::FromInt(StatusCode), *Reason, bWasClean);
            });
       
            WebSocket->Connect(Url);
	}
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Could not create Web Socket"));
    }

}


void FWebSocketClient::Disconnect()
{
    if(WebSocket.IsValid())
    {
        WebSocket->Close();
        WebSocket.Reset();
         bIsConnected = false;
     }
}

void FWebSocketClient::SendMessage(const FString& Event, const FString& Message)
{

    if(WebSocket.IsValid() && bIsConnected)
    {
        TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Message);
         FString JsonString;
        if (FJsonSerializer::Serialize(TJsonWriterFactory<>::Create(&JsonString),  Message))
        {
           WebSocket->Send(TEXT("{\"audio_data\":") +  JsonString + TEXT("}"));
        }
         else
        {
            UE_LOG(LogTemp, Error, TEXT("Could not serialise message"))
        }

    }
    else
    {
         UE_LOG(LogTemp, Error, TEXT("Websocket is invalid or not Connected"));
    }
}

bool FWebSocketClient::IsConnected() const
{
	return bIsConnected;
}