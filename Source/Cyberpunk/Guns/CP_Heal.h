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

	// ������ �ĺ��� �̸� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	FName ItemName;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* HealMesh;
};
