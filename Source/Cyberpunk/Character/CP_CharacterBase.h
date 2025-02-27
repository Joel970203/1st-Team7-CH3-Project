#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"

#include "CP_CharacterBase.generated.h"

UENUM()
enum class ETeamType : uint8
{
	EnemyTeam = 0,
	PlayerTeam = 1,
	Neutral = 255
};

UCLASS()
class CYBERPUNK_API ACP_CharacterBase : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:

	ACP_CharacterBase();

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override;

public:

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:

	virtual void Die();

	// getter, setter
public:

	UFUNCTION(BlueprintCallable)
	bool IsDead();

	UFUNCTION(BlueprintCallable)
	int32 GetMaxHP();

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentHp();

	UFUNCTION(BlueprintCallable)
	ETeamType GetTeamType();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CPCharacter")
	int32 MaxHp = 1;

	// ���� ȿ�� ����ؼ� CurrentHp, BaseHp ����.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CPCharacter")
	int32 CurrentHp = 1;

	// ���� ü���� �ǹ�
	UPROPERTY(EditAnywhere, Category = "CPCharacter")
	int32 BaseHp = 1;

	// ���� ȿ�� ����ؼ� Current Armor, Base Armor ����.
	UPROPERTY(EditAnywhere, Category = "CPCharacter")
	int32 CurrentArmor = 1;

	// ���� ������ �ǹ�
	UPROPERTY(EditAnywhere, Category = "CPCharacter")
	int32 BaseArmor = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CPCharacter")
	bool bIsDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CPCharacter")
	ETeamType TeamType;

	FGenericTeamId TeamId;
};
