#ifndef PHYSICS_H
#define PHYSICS_H
#if defined(_MSC_VER) || (defined(__GNUC__) && __GNUC__ > 3)
	#pragma once
#endif

#include <utlhashtable.h>

class IPhysicsEnvironment;
class IPhysicsCollisionSet;

class CPhysics : public CTier1AppSystem<IPhysics32> {
	typedef CTier1AppSystem<IPhysics32> BaseClass;
	public:
		~CPhysics();
        bool                        Connect( CreateInterfaceFn factory );
        void                        Disconnect( void );
		void *						QueryInterface(const char *pInterfaceName);
		InitReturnVal_t				Init();
		void						Shutdown();

		IPhysicsEnvironment *		CreateEnvironment();
		void						DestroyEnvironment(IPhysicsEnvironment *pEnv);
		IPhysicsEnvironment *		GetActiveEnvironmentByIndex(int index);
		int							GetActiveEnvironmentCount();

		IPhysicsObjectPairHash *	CreateObjectPairHash();
		void						DestroyObjectPairHash(IPhysicsObjectPairHash *pHash);

		IPhysicsCollisionSet *		FindOrCreateCollisionSet( uintptr_t id, int maxElementCount);
		IPhysicsCollisionSet *		FindCollisionSet( uintptr_t id);
		void						DestroyAllCollisionSets();

        IVPhysicsDebugOverlay *         GetPhysicsDebugOverlay() { return m_pPhysicsDebugOverlay; }
	private:
		CUtlVector<IPhysicsEnvironment *>	m_envList;
		CUtlVector<IPhysicsCollisionSet *>	m_collisionSets;
		CUtlHashtable<unsigned int, unsigned int> m_colSetTable;
		IVPhysicsDebugOverlay *m_pPhysicsDebugOverlay;
};

extern CPhysics g_Physics;

#endif
   registerSearch: (callback: Callback) => ipcRenderer.on('search', callback),
    registerFileSearch: (callback: Callback) =>
        ipcRenderer.on('fileSearch', callback),
    registerCommandPalette: (callback: Callback) =>
        ipcRenderer.on('commandPalette', callback),
    ...clientPreloads(),
    registerGetDefinition(callback: (arg: any) => void) {
        ipcRenderer.on('getDefinition', (event, data) => {
            callback(data)
        })
    },
    registerAddCodeToPrompt(callback: (arg: any) => void) {
        ipcRenderer.on('addCodeToPrompt', (event, data) => {
            callback(data)
        })
    },
    setCookies: async (cookieObject: {
        url: string
        name: string
        value: string
    }) => {
        await ipcRenderer.invoke('setCookies', cookieObject)
    },
    loginCursor: async () => {
        await ipcRenderer.invoke('loginCursor')
    },
    logoutCursor: async () => {
        await ipcRenderer.invoke('logoutCursor')
    },
    getUserCreds: async () => {
        return await ipcRenderer.invoke('getUserCreds')
    },
    payCursor: async () => {
        return await ipcRenderer.invoke('payCursor')
    },
    registerUpdateAuthStatus(
        callback: (payload: {
            accessToken?: string | null
            profile?: any | null
            stripeProfile?: string | null
        }) => void
    ) {
        ipcRenderer.on('updateAuthStatus', (event, data) => {
            console.log('UPDATING AUTH STATUS', data)
            callback(data)
        })
    },
    refreshTokens() {
        ipcRenderer.invoke('refreshTokens')
    },
    registerCloseErrors(callback: Callback) {
        ipcRenderer.on('closeErrors', callback)
    },
}

contextBridge.exposeInMainWorld('connector', electronConnector)
type ElectronConnector = typeof electronConnector
export default ElectronConnector
export const loginStatus = createSelector(
    (state: FullState) => state.toolState,
    (tool: ToolState) => ({
        signedIn: !!(tool.cursorLogin.accessToken && tool.cursorLogin.profile),
        proVersion: !!tool.cursorLogin.stripeId,
    })
)
