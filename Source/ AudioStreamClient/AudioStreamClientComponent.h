// Source/AudioStreamClient/AudioStreamClientComponent.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WebSocketClient.h"
#include "AudioStreamClientComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AUDIOSTREAMCLIENT_API UAudioStreamClientComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
    UAudioStreamClientComponent();

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category = "Audio Streaming")
    void StartAudioStreaming();

    UFUNCTION(BlueprintCallable, Category = "Audio Streaming")
    void StopAudioStreaming();

     UFUNCTION(BlueprintImplementableEvent, Category = "Audio Streaming")
    void OnJsonDataReceived(const FString& JsonData);

      UFUNCTION(BlueprintImplementableEvent, Category = "Audio Streaming")
    void OnErrorReceived(const FString& Error);

    FString WebSocketUrl = TEXT("ws://localhost:3000"); // Backend Server URL
    FString ErrorMessage;

protected:
    void OnWebSocketMessage(const FString& Message);

    void OnWebSocketError(const FString& Error);

    bool IsRecording = false;

    int32 SampleRate = 44100;

    FWebSocketClient WebSocketClient;

    TArray<uint8> AudioBuffer;
};