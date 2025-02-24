#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_Heal.generated.h"

UCLASS()
class CYBERPUNK_API ACP_Heal : public AActor
{
	GENERATED_BODY()

public:
	ACP_Heal();

protected:
	// Heal �����ۿ� ����ƽ �޽� ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* HealMesh;
};
