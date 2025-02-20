#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "CP_Projectile.generated.h"

UCLASS()
class CYBERPUNK_API ACP_Projectile : public AActor
{
    GENERATED_BODY()

public:
    ACP_Projectile();

protected:
    virtual void BeginPlay() override;

public:
    // Root Scene Component
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USceneComponent* RootScene;  // ��Ʈ ������Ʈ �߰�

    // Projectile Mesh
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UStaticMeshComponent* ProjectileMesh;

    // Projectile Movement
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
    UProjectileMovementComponent* ProjectileMovement;

    // �߻� �Լ� �߰�
    UFUNCTION(BlueprintCallable, Category = "Projectile")
    void LaunchProjectile(const FVector& LaunchDirection);
};
