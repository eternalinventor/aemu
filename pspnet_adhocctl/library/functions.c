#include "common.h"

/**
 * Resolve IP to MAC
 * @param ip Peer IP Address
 * @param mac OUT: Peer MAC
 * @return 0 on success or... ADHOC_NO_ENTRY
 */
int _resolveIP(uint32_t ip, SceNetEtherAddr * mac)
{
	// Multithreading Lock
	_acquirePeerLock();
	
	// Peer Reference
	SceNetAdhocctlPeerInfo * peer = _friends;
	
	// Iterate Peers
	for(; peer != NULL; peer = peer->next)
	{
		// Found Matching Peer
		if(peer->ip_addr == ip)
		{
			// Copy Data
			*mac = peer->mac_addr;
			
			// Multithreading Unlock
			_freePeerLock();
			
			// Return Success
			return 0;
		}
	}
	
	// Multithreading Unlock
	_freePeerLock();
	
	// Peer not found
	return ADHOC_NO_ENTRY;
}

/**
 * Resolve MAC to IP
 * @param mac Peer MAC Address
 * @param ip OUT: Peer IP
 * @return 0 on success or... ADHOC_NO_ENTRY
 */
int _resolveMAC(SceNetEtherAddr * mac, uint32_t * ip)
{
	// Multithreading Lock
	_acquirePeerLock();
	
	// Peer Reference
	SceNetAdhocctlPeerInfo * peer = _friends;
	
	// Iterate Peers
	for(; peer != NULL; peer = peer->next)
	{
		// Found Matching Peer
		if(memcmp(&peer->mac_addr, mac, sizeof(SceNetEtherAddr)) == 0)
		{
			// Copy Data
			*ip = peer->ip_addr;
			
			// Multithreading Unlock
			_freePeerLock();
			
			// Return Success
			return 0;
		}
	}
	
	// Multithreading Unlock
	_freePeerLock();
	
	// Peer not found
	return ADHOC_NO_ENTRY;
}

/**
 * Get First Peer List Element
 * @return First Internal Peer List Element
 */
SceNetAdhocctlPeerInfo * _getInternalPeerList(void)
{
	// Return First Peer List Element
	return _friends;
}