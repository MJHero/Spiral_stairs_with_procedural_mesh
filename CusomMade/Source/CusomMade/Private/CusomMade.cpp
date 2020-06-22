// Copyright 1998-2020 MUJI tech, Inc. All Rights Reserved.

#include "CusomMade.h"

#define LOCTEXT_NAMESPACE "FCusomMadeModule"

void FCusomMadeModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FCusomMadeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCusomMadeModule, CusomMade)