#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "CP_CharacterBase.generated.h"

UCLASS()
class CYBERPUNK_API ACP_CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:

	ACP_CharacterBase();

protected:

	virtual void BeginPlay() override;
	//virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:

	virtual void Die();

protected:

	UPROPERTY(EditAnywhere, Category = "CPCharacter")
	int32 MaxHp = 1;

	// ���� ȿ�� ����ؼ� CurrentHp, BaseHp ����.
	UPROPERTY(EditAnywhere, Category = "CPCharacter")
	int32 CurrentHp = 1;

	UPROPERTY(EditAnywhere, Category = "CPCharacter")
	int32 BaseHp = 1;

	// ���� ȿ�� ����ؼ� Current Armor, Base Armor ����.
	UPROPERTY(EditAnywhere, Category = "CPCharacter")
	int32 CurrentArmor = 1;

	UPROPERTY(EditAnywhere, Category = "CPCharacter")
	int32 BaseArmor = 1;

};
