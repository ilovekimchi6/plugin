// Source/AudioStreamClient/AudioStreamClientComponent.cpp
#include "AudioStreamClientComponent.h"
#include "WebSocketsModule.h"
#include "Misc/Base64.h"
#include "AudioCapture.h"


UAudioStreamClientComponent::UAudioStreamClientComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
    bWantsInitializeComponent = true;
}

void UAudioStreamClientComponent::InitializeComponent()
{
  Super::InitializeComponent();
}

void UAudioStreamClientComponent::BeginPlay()
{
	Super::BeginPlay();

    WebSocketClient.OnMessage.BindUObject(this, &UAudioStreamClientComponent::OnWebSocketMessage);
    WebSocketClient.OnError.BindUObject(this, &UAudioStreamClientComponent::OnWebSocketError);
    WebSocketClient.Connect(WebSocketUrl);
}


void UAudioStreamClientComponent::StartAudioStreaming()
{
    if(!IsRecording){
    AudioBuffer.Empty(); // Clear buffer before starting recording
        FAudioCapture AudioCapture;
        AudioCapture.Start();
        AudioCapture.OnAudioCapture.BindLambda([this](const TArray<uint8>& CapturedAudio)
        {
            if(IsRecording) {
                this->AudioBuffer.Append(CapturedAudio);

                 FString Base64String = FBase64::Encode(AudioBuffer);

                 if(WebSocketClient.IsConnected())
                    {
                     WebSocketClient.SendMessage(TEXT("audio_data"), Base64String);
                    }
                    else
                    {
                        ErrorMessage = TEXT("Web Socket not Connected!");
                        OnErrorReceived(ErrorMessage);
                    }


                    AudioBuffer.Empty(); // clear for next time!
               }
        });

        IsRecording = true;
    }
    else
    {
        ErrorMessage = TEXT("Already recording!");
        OnErrorReceived(ErrorMessage);
    }

}


void UAudioStreamClientComponent::StopAudioStreaming()
{
    if (IsRecording)
    {
         FAudioCapture AudioCapture;
        AudioCapture.Stop();
        IsRecording = false;
     }
    else
    {
        ErrorMessage = TEXT("Not recording!");
         OnErrorReceived(ErrorMessage);
    }
}


void UAudioStreamClientComponent::OnWebSocketMessage(const FString& Message)
{
    OnJsonDataReceived(Message); // Forward the message to the Blueprint
}

void UAudioStreamClientComponent::OnWebSocketError(const FString& Error)
{
     OnErrorReceived(Error); // Forward the error message
}