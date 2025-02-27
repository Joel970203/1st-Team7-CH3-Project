#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_Gear.generated.h"

UCLASS()
class CYBERPUNK_API ACP_Gear : public AActor
{
	GENERATED_BODY()

public:
	ACP_Gear();

	// ������ �ĺ��� �̸� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	FName ItemName;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* GearMesh;
};
