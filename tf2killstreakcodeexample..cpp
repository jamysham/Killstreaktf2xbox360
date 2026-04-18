#include "stdafx.h"

// just a simple plugin that does the killstreak
#include <stdio.h>

#define MAX_PLAYERS 24

int g_Killstreak[MAX_PLAYERS];

const char* GetPlayerName(int index); 
void ShowGameText(int player, const char* text); 
void ShowKillFeed(const char* text); 

void ResetPlayer(int player)
{
    if (player < 0 || player >= MAX_PLAYERS)
        return;

    g_Killstreak[player] = 0;
}

void OnPlayerKilled(int attacker, int victim)
{
    if (attacker < 0 || attacker >= MAX_PLAYERS || victim < 0 || victim >= MAX_PLAYERS)
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

    
    int streak = g_Killstreak[attacker];
    if (streak % 5 == 0 && streak > 0)
    {
        char msg[256];
        const char* streakName = "KILLING SPREE";
        if (streak == 10) streakName = "RAMPAGE";
        else if (streak == 15) streakName = "UNSTOPPABLE";
        else if (streak >= 20) streakName = "GOD-LIKE";

        snprintf(msg, sizeof(msg), "%s is on a %s! (%d)", attackerName, streakName, streak);
        ShowGameText(-1, msg);
    }

    
    if (victimStreak >= 5)
    {
        char feed[256];
        char text[256];

        snprintf(feed, sizeof(feed), "%s ended %s's rampage!", attackerName, victimName);
        snprintf(text, sizeof(text), "%s ended %s's Kill streak!", attackerName, victimName);

        ShowKillFeed(feed);
        ShowGameText(-1, text);
    }
}
