// Fill out your copyright notice in the Description page of Project Settings.

#include "Dev/MYDamageSphereActor.h"
#include <DrawDebugHelpers.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
AMYDamageSphereActor::AMYDamageSphereActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    SetRootComponent(SceneComponent);
}

// Called when the game starts or when spawned
void AMYDamageSphereActor::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AMYDamageSphereActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor);
    DrawDebugPoint(GetWorld(), GetActorLocation(), 10.0f, SphereColor);

    UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, DamageType, {}, this, nullptr, DoFullDamage);
}
