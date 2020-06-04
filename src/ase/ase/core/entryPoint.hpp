#pragma once

#include <asepch.hpp>

static ase::PluginInterface* plugin;

using namespace std;

static float handleFlCallback (
                                   float                inElapsedSinceLastCall,    
                                   float                inElapsedTimeSinceLastFlightLoop,    
                                   int                  inCounter,    
                                   void *               inRefcon)
{

    plugin->Update();

    /* Return 0.01 to indicate that we want to be called again in 1 ms. */
    return 0.01;
}    

PLUGIN_API int XPluginStart(
						char *		outName,
						char *		outSig,
						char *		outDesc)
{
    plugin = ase::PluginManager::RegisterPlugin();

	strcpy(outName, plugin->m_name.c_str());
	strcpy(outSig, plugin->m_sig.c_str());
	strcpy(outDesc, plugin->m_desc.c_str());

    plugin->Start();

    XPLMRegisterFlightLoopCallback(		
            handleFlCallback,	/* Callback */
            0.01,					/* Interval */
            NULL);	
					
	return 1;
}

PLUGIN_API void	XPluginStop()
{
    plugin->Stop();
    free(plugin);
}

PLUGIN_API int XPluginEnable()
{
    plugin->Enable();
	return 1;
}

PLUGIN_API void XPluginDisable()
{
    plugin->Disable();
}


PLUGIN_API void XPluginReceiveMessage(
					XPLMPluginID	inFromWho,
					long			inMessage,
					void *			inParam)
{
}
