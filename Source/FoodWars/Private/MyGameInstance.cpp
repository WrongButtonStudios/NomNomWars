// MyGameInstance.cpp
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UMyGameInstance::Init()
{
    Super::Init();

    FCoreDelegates::OnControllerConnectionChange.AddUObject(
        this,
        &UMyGameInstance::HandleControllerConnection
    );

    UE_LOG(LogTemp, Warning, TEXT("GameInstance gestartet!"));
}

void UMyGameInstance::Shutdown()
{
    // Controller-Events deregistrieren
    FCoreDelegates::OnControllerConnectionChange.RemoveAll(this);

    Super::Shutdown();
    UE_LOG(LogTemp, Warning, TEXT("GameInstance beendet!"));
}

void UMyGameInstance::HandleControllerConnection(bool bIsConnected, FPlatformUserId UserId, int32 UserIndex)
{


   FString ControllerIdStr = GenerateControllerId(UserId, UserIndex);
    if (bIsConnected)
    {
        int32 PlayerIndex = -1;

        if (TryReconnectController(ControllerIdStr, PlayerIndex))
        {
            UE_LOG(LogTemp, Warning, TEXT("Controller %s reconnected für Player %d"), *ControllerIdStr, PlayerIndex);
        }
        else
        {
            TSet<int32> UsedIndices;
            for (const auto& Pair : ConnectedControllers)
            {
                if (Pair.Value.bIsConnected)
                {
                    UsedIndices.Add(Pair.Value.PlayerIndex);
                }
            }

            for (int32 i = 0; i < 4; ++i)
            {
                if (!UsedIndices.Contains(i))
                {
                    PlayerIndex = i;
                    break;
                }
            }

            if (PlayerIndex != -1)
            {
                ConnectedControllers.Add(ControllerIdStr, FControllerData(PlayerIndex, ControllerIdStr));
                UE_LOG(LogTemp, Warning, TEXT("Neuer Controller %s verbunden als Player %d"), *ControllerIdStr, PlayerIndex);
                SetIsDebugging(true);
            }
        }
    }
    else
    {
        if (FControllerData* Data = ConnectedControllers.Find(ControllerIdStr))
        {
            Data->bIsConnected = false;
            UE_LOG(LogTemp, Warning, TEXT("Controller %s getrennt (war Player %d)"), *ControllerIdStr, Data->PlayerIndex);
        }
    }
}

FString UMyGameInstance::GenerateControllerId(FPlatformUserId UserId, int32 UserIndex)
{
    return FString::Printf(TEXT("Controller_User%d_Index%d"), static_cast<int32>(UserId), UserIndex);
}

bool UMyGameInstance::TryReconnectController(const FString& ControllerId, int32& OutPlayerIndex)
{
    if (const FControllerData* Data = ConnectedControllers.Find(ControllerId))
    {
        OutPlayerIndex = Data->PlayerIndex;
        ConnectedControllers[ControllerId].bIsConnected = true;
        return true;
    }
    return false;
}

void UMyGameInstance::CheckControllers()
{
    // Zeige Anzahl der Controller an
    for (const auto& Pair : ConnectedControllers)
    {
        if (Pair.Value.bIsConnected)
        {
            GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Green,
                FString::Printf(TEXT("Controller ID: %s ist verbunden"), *Pair.Key));
            SetIsDebugging(true);
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red,
                FString::Printf(TEXT("Controller ID: %s ist getrennt"), *Pair.Key));
            
        }
    }

    // Falls keine Controller registriert sind
    if (ConnectedControllers.Num() == 0)
    {
        GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Yellow, TEXT("Keine Controller registriert"));
        
    }
}



//GAMEINSTANCE VALUES
//GAMEINSTANCE VALUES
//GAMEINSTANCE VALUES
//GAMEINSTANCE VALUES
//GAMEINSTANCE VALUES
//GAMEINSTANCE VALUES
int32 UMyGameInstance::GetZombieDiceResult() const
{
	return ZombieDiceResult;
}

void UMyGameInstance::SetZombieDiceResult(int32 NewValue)
{
	ZombieDiceResult = NewValue;
}

int32 UMyGameInstance::GetWeaponDiceResult() const
{
	return WeaponDiceResult;
}

void UMyGameInstance::SetWeaponDiceResult(int32 NewValue)
{
	WeaponDiceResult = NewValue;
}

int32 UMyGameInstance::GetNumberOfPlayers() const
{
	return NumberOfPlayers;
}

void UMyGameInstance::SetNumberOfPlayers(int32 NewValue)
{
	NumberOfPlayers = NewValue;
}

int32 UMyGameInstance::GetTurnTimer() const
{
	return TurnTimer;
}

void UMyGameInstance::SetTurnTimer(int32 NewValue)
{
	TurnTimer = NewValue;
}

int32 UMyGameInstance::GetPlayerInTurn() const
{
	return PlayerInTurn;
}

void UMyGameInstance::SetPlayerInTurn(int32 NewValue)
{
	PlayerInTurn = NewValue;
}

bool UMyGameInstance::IsKingKillerActive() const
{
	return bIsKingKillerActive;
}

void UMyGameInstance::SetKingKillerActive(bool bActive)
{
	bIsKingKillerActive = bActive;
}

bool UMyGameInstance::IsPawnPuncherActive() const
{
	return bIsPawnPuncherActive;
}


void UMyGameInstance::SetPawnPuncherActive(bool bActive)
{
	bIsPawnPuncherActive = bActive;
}

bool UMyGameInstance::IsDebugging() const
{
    return bIsDebugging;
}

void UMyGameInstance::SetIsDebugging(bool bDebugging)
{
    bIsDebugging = bDebugging;
}