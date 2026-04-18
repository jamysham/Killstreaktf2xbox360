#include "stdafx.h"

// just a simple plugin that does the killstreak
#include <stdio.h>

#define MAX_PLAYERS 24

int g_Killstreak[MAX_PLAYERS];
int g_LastVictimStreak[MAX_PLAYERS];

const char* GetPlayerName(int index); 
void ShowGameText(int player, const char* text); 
void ShowKillFeed(const char* text); 

static char buffer[256];

static const char* Format(const char* fmt, const char* a, const char* b = nullptr)
{
    sprintf(buffer, fmt, a, b ? b : "");
    return buffer;
}

void ResetPlayer(int player)
{
    g_Killstreak[player] = 0;
}

void OnPlayerKilled(int attacker, int victim)
{
    if (attacker < 0 || victim < 0)
        return;

    if (attacker == victim)
    {
        ResetPlayer(victim);
        return;
    }

    
    int victimStreak = g_Killstreak[victim];


    g_Killstreak[attacker]++;

    // Reset victim
    ResetPlayer(victim);

    const char* attackerName = GetPlayerName(attacker);
    const char* victimName = GetPlayerName(victim);

    
    if (g_Killstreak[attacker] == 5)
    {
        char msg[256];
        sprintf(msg, "%s is on a KILLING SPREE! (5)", attackerName);

        ShowGameText(-1, msg);
    }

    
    if (victimStreak >= 5)
    {
        char feed[256];
        char text[256];

        sprintf(feed, "%s captured Their rampage is no more!", attackerName);
        sprintf(text, "%s ended %s's Kill streak!", attackerName, victimName);

        ShowKillFeed(feed);
        ShowGameText(-1, text);
    }
}
