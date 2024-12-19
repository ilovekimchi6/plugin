// Source/AudioStreamClient/AudioStreamClient.cpp
#include "AudioStreamClient.h"

#define LOCTEXT_NAMESPACE "FAudioStreamClientModule"

void FAudioStreamClientModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module.

}

void FAudioStreamClientModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up resources.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAudioStreamClientModule, AudioStreamClient)