#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"  // Niagara �ý����� ����ϱ� ���� ��� �߰�
#include "NiagaraFunctionLibrary.h"  // Niagara �ý��� �Լ� ���̺귯�� �߰�
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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    USphereComponent* CollisionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UNiagaraComponent* NiagaraEffect;

    // Projectile Movement
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
    UProjectileMovementComponent* ProjectileMovement;

    // �߻� �Լ�
    UFUNCTION(BlueprintCallable, Category = "Projectile")
    void LaunchProjectile(const FVector& LaunchDirection);

private:
    // �浹 �߻� �� ȣ��� �Լ�
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        FVector NormalImpulse, const FHitResult& Hit);
};
