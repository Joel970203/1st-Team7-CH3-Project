#include "CP_PauseMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetTree.h"
#include "Kismet/KismetSystemLibrary.h"

UCP_PauseMenu::UCP_PauseMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCP_PauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UCP_PauseMenu::OnResumeButtonClicked);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CP_PauseMenu: ResumeButton ������ ���ε����� �ʾҽ��ϴ�."));
	}

	if (ExitFromPauseButton)
	{
		ExitFromPauseButton->OnClicked.AddDynamic(this, &UCP_PauseMenu::OnExitFromPauseButtonClicked);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CP_PauseMenu: ExitFromPauseButton ������ ���ε����� �ʾҽ��ϴ�."));
	}
}


void UCP_PauseMenu::OnResumeButtonClicked()
{
	// �Ͻ����� �޴� ���� (ȭ�鿡�� ����)
	RemoveFromParent();
	// ���� �簳 ���� (Unpause ��, �ʿ��ϸ� ���⿡ ����)
	UE_LOG(LogTemp, Warning, TEXT("CP_PauseMenu: Resume Button Clicked"));
}

void UCP_PauseMenu::OnExitFromPauseButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
	UE_LOG(LogTemp, Warning, TEXT("CP_PauseMenu: Exit from Pause Button Clicked"));
}