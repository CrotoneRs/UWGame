#include "PerkComponent.h"
#include "UwGameState.h"
#include "Components/SphereComponent.h"
#include "GameFramework/PlayerState.h"

UPerkComponent::UPerkComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMoreTimePerkComponent::ApplyPerk() const
{
	AUwGameState* GameState = Cast<AUwGameState>(GetWorld()->GetGameState());

	if (GameState)
	{
		GameState->RemainingTime += 10.0f;

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(0, 2, FColor::Magenta, "UMoreTimePerkComponent +10s");
		}
	}
}

APerkActor::APerkActor()
{
	PerkRadius = CreateDefaultSubobject<USphereComponent>("PerkRadius");

	PerkRadius->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	PerkRadius->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	PerkRadius->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void APerkActor::BeginPlay()
{
	Super::BeginPlay();

	// PerkComponent Instanciate

	FScriptDelegate OnComponentBeginOverlapDelegate;
	OnComponentBeginOverlapDelegate.BindUFunction(this, "OnComponentBeginOverlap");

	FScriptDelegate OnComponentEndOverlapDelegate;
	OnComponentEndOverlapDelegate.BindUFunction(this, "OnComponentEndOverlap");

	PerkRadius->OnComponentBeginOverlap.AddUnique(OnComponentBeginOverlapDelegate);
	PerkRadius->OnComponentEndOverlap.AddUnique(OnComponentEndOverlapDelegate);
}

void APerkActor::EndPlay(const EEndPlayReason::Type Reason)
{
	PerkRadius->OnComponentBeginOverlap.RemoveAll(this);
	PerkRadius->OnComponentEndOverlap.RemoveAll(this);

	Super::EndPlay(Reason);
}

void APerkActor::OnComponentBeginOverlap(UPrimitiveComponent* ThisComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UPerkComponent* PerkComponent = Cast<UPerkComponent>(OtherComponent))
	{
		PerkComponent->ApplyPerk();
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Blue, "PerkComponent OnComponentBeginOverlap");
	}
}

void APerkActor::OnComponentEndOverlap(UPrimitiveComponent* ThisComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Blue, "PerkComponent OnComponentEndOverlap");
	}
}
