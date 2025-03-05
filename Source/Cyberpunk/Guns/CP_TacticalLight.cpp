#include "CP_TacticalLight.h"
#include "Components/SpotLightComponent.h"

// ������
ACP_TacticalLight::ACP_TacticalLight()
{
	PrimaryActorTick.bCanEverTick = false;

	// ��Ʈ �� ����
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	//  Tactical Spot Light �߰� (���� ����)
	TacticalSpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("TacticalSpotLight"));
	TacticalSpotLight->SetupAttachment(RootScene);

	// Spot Light �⺻ ����
	TacticalSpotLight->SetIntensity(50000.0f); // ���� ���� (�⺻ ������ ���� ����)
	TacticalSpotLight->SetLightColor(FLinearColor::Yellow); // �� ����
	TacticalSpotLight->SetAttenuationRadius(1000.0f); // ���� �Ÿ� (���� ������ ����)
	TacticalSpotLight->SetOuterConeAngle(35.0f); // �� ������ ���� (����)
	TacticalSpotLight->SetInnerConeAngle(20.0f); // �߽� ���� ����
	TacticalSpotLight->SetVisibility(false); // �⺻������ ��Ȱ��ȭ Ű ���ε����� Ȱ��ȭ

	//  ���� ���� ���� (������ ���ߵ��� ����)
	TacticalSpotLight->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));

	TacticalSpotLight->SetRelativeLocation(FVector(0.0f, 0.0f, -8.0f));
	//  Tactical Light�� Static Mesh �ε�
	TArray<FString> MeshPaths = {
		TEXT("/Game/Gun_BluePrint/tacticalLight/FL_Clip.FL_Clip"),
		TEXT("/Game/Gun_BluePrint/tacticalLight/FL_End_1.FL_End_1"),
		TEXT("/Game/Gun_BluePrint/tacticalLight/FL_End_2.FL_End_2"),
		TEXT("/Game/Gun_BluePrint/tacticalLight/FL_Handle.FL_Handle"),
		TEXT("/Game/Gun_BluePrint/tacticalLight/FL_Head.FL_Head"),
		TEXT("/Game/Gun_BluePrint/tacticalLight/FL_Neck_1.FL_Neck_1"),
		TEXT("/Game/Gun_BluePrint/tacticalLight/FL_Neck_2.FL_Neck_2")
	};

	for (const FString& Path : MeshPaths)
	{
		UStaticMesh* LoadedMesh = LoadObject<UStaticMesh>(nullptr, *Path);
		if (LoadedMesh)
		{
			PreloadedMeshes.Add(LoadedMesh);
		}
	}
}


void ACP_TacticalLight::BeginPlay()
{
	Super::BeginPlay();

	for (UStaticMesh* Mesh : PreloadedMeshes)
	{
		if (Mesh)
		{
			AddLightPart(Mesh);
		}
	}
}


void ACP_TacticalLight::AddLightPart(UStaticMesh* Mesh, FTransform Transform)
{
	if (!Mesh) return;

	UStaticMeshComponent* NewMeshComponent = NewObject<UStaticMeshComponent>(this);

	if (NewMeshComponent)
	{
		NewMeshComponent->SetStaticMesh(Mesh);
		NewMeshComponent->SetupAttachment(RootScene);
		NewMeshComponent->SetRelativeTransform(Transform);
		NewMeshComponent->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
		NewMeshComponent->RegisterComponent();
	}
}

void ACP_TacticalLight::ToggleLight()
{
	if (TacticalSpotLight)
	{
		UE_LOG(LogTemp, Warning, TEXT("[ACP_TacticalLight] ToggleLight() called! TacticalSpotLight exists."));
		TacticalSpotLight->SetVisibility(true);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[ACP_TacticalLight] ERROR: TacticalSpotLight is nullptr!"));
	}
}
