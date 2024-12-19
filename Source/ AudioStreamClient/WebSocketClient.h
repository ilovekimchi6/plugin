// Source/AudioStreamClient/WebSocketClient.h
#pragma once

#include "CoreMinimal.h"
#include "WebSocketsModule.h"
#include "Containers/UnrealString.h"


DECLARE_DELEGATE_OneParam(FWebSocketMessageDelegate, const FString&);
DECLARE_DELEGATE_OneParam(FWebSocketErrorDelegate, const FString&);


class FWebSocketClient
{
public:
    FWebSocketClient();
    ~FWebSocketClient();

    void Connect(const FString& Url);
    void Disconnect();
    void SendMessage(const FString& Event, const FString& Message);
    bool IsConnected() const;

     FWebSocketMessageDelegate OnMessage;
     FWebSocketErrorDelegate OnError;

private:
    TSharedPtr<IWebSocket> WebSocket;
    bool bIsConnected = false;
};