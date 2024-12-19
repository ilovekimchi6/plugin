// Source/AudioStreamClient/AudioStreamClient.h
#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"


class FAudioStreamClientModule : public IModuleInterface
{
public:
	// IModuleInterface interface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};