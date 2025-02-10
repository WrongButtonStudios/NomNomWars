// MyGameInstance.h
#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Delegates/Delegate.h"  // Für FCoreDelegates
#include "MyGameInstance.generated.h"

USTRUCT()
struct FControllerData
{
    GENERATED_BODY()
    
    UPROPERTY()
    int32 PlayerIndex;
    
    UPROPERTY()
    FString ControllerId;
    
    UPROPERTY()
    bool bIsConnected;

    FControllerData() : PlayerIndex(-1), bIsConnected(false) {}
    FControllerData(int32 InPlayerIndex, const FString& InControllerId)
        : PlayerIndex(InPlayerIndex), ControllerId(InControllerId), bIsConnected(true) {}
};


UCLASS()
class FOODWARS_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	/** Initialisierung der GameInstance */
	virtual void Init() override;
	/** Aufräumen bei Spielende */
	virtual void Shutdown() override;

	/** Getter und Setter für Game-Variablen */
	UFUNCTION(BlueprintCallable, Category = "Game Data")
	int32 GetZombieDiceResult() const;

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void SetZombieDiceResult(int32 NewValue);

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	int32 GetWeaponDiceResult() const;

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void SetWeaponDiceResult(int32 NewValue);

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	int32 GetNumberOfPlayers() const;

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void SetNumberOfPlayers(int32 NewValue);

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	int32 GetTurnTimer() const;

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void SetTurnTimer(int32 NewValue);

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	int32 GetPlayerInTurn() const;

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void SetPlayerInTurn(int32 NewValue);

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	bool IsKingKillerActive() const;

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void SetKingKillerActive(bool bActive);

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	bool IsPawnPuncherActive() const;


	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void SetPawnPuncherActive(bool bActive);
	
	UFUNCTION(BlueprintCallable, Category = "Game Data")
	bool IsDebugging() const;

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void SetIsDebugging(bool bDebugging);

	UFUNCTION(BlueprintCallable, Category = "Controller")
	void HandleControllerConnection(bool bIsConnected, FPlatformUserId UserId, int32 UserIndex);

	UFUNCTION(BlueprintCallable, Category = "Controller")
	FString GenerateControllerId(FPlatformUserId UserId, int32 UserIndex);

	UFUNCTION(BlueprintCallable, Category = "Controller")
	bool TryReconnectController(const FString& ControllerId, int32& OutPlayerIndex);

	// Im Header (MyGameInstance.h)
	UFUNCTION(BlueprintCallable, Category = "Controller Debug")
	void CheckControllers();


private:
	/** Variablen für den KingKiller */
	UPROPERTY(BlueprintReadWrite, Category = "Game Data", meta = (AllowPrivateAccess = "true"))
	int32 ZombieDiceResult = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Game Data", meta = (AllowPrivateAccess = "true"))
	int32 WeaponDiceResult = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Game Data", meta = (AllowPrivateAccess = "true"))
	int32 NumberOfPlayers = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Game Data", meta = (AllowPrivateAccess = "true"))
	int32 TurnTimer = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Game Data", meta = (AllowPrivateAccess = "true"))
	int32 PlayerInTurn = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Game Data", meta = (AllowPrivateAccess = "true"))
	bool bIsKingKillerActive = false;

	UPROPERTY(BlueprintReadWrite, Category = "Game Data", meta = (AllowPrivateAccess = "true"))
	bool bIsPawnPuncherActive = false;

	UPROPERTY(BlueprintReadWrite, Category = "Game Data", meta = (AllowPrivateAccess = "true"))
	bool bIsDebugging = false;

	// Controller-Management
	UPROPERTY()
	TMap<FString, FControllerData> ConnectedControllers;
	
};