// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PerkComponent.generated.h"


UCLASS( Abstract )
class UWGAME_API UPerkComponent : public USceneComponent
{
	GENERATED_BODY()

public:	UPerkComponent();

	virtual void ApplyPerk() const PURE_VIRTUAL(UPerkComponent::ApplyPerk);
};

UCLASS(Blueprintable)
class UWGAME_API UMoreTimePerkComponent : public UPerkComponent
{
	GENERATED_BODY()

public: UMoreTimePerkComponent() = default;

	virtual void ApplyPerk() const override;
};

UCLASS(Blueprintable)
class UWGAME_API APerkActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPerkComponent> PerkComponentClass;

	UPROPERTY()
	UPerkComponent* PerkComponent;

	UPROPERTY()
	class USphereComponent* PerkRadius;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* ThisComponent, AActor* OtherActor,
		UPrimitiveComponent* OhterComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* ThisComponent, AActor* OtherActor,
		UPrimitiveComponent* OhterComponent, int32 OtherBodyIndex);

public: APerkActor();

	  virtual void BeginPlay() override;
	  virtual void EndPlay(const EEndPlayReason::Type Reason) override;
};
