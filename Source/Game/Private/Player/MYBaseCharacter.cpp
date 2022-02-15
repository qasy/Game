// Fill out your copyright notice in the Description page of Project Settings.

#include <Player/MYBaseCharacter.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Player/Components/MYHealthComponent.h>
#include <Components/TextRenderComponent.h>

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All)

// Sets default values
AMYBaseCharacter::AMYBaseCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

    SpringArmComponent->SetupAttachment(GetRootComponent());
    CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

    SpringArmComponent->bUsePawnControlRotation = true;

    HealthComponent = CreateDefaultSubobject<UMYHealthComponent>("HealthComponent");

    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
    HealthTextComponent->SetupAttachment(GetRootComponent());

    // GetCharacterMovement()->bOrientRotationToMovement = true;
    // GetCharacterMovement()->bUseControllerDesiredRotation = true;
    // GetCharacterMovement()->bIgnoreBaseRotation = true;
}

// Called when the game starts or when spawned
void AMYBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
    check(HealthComponent);
    check(HealthTextComponent);
    check(GetCharacterMovement());

    OnHealthChanged(HealthComponent->GetHealth());
    HealthComponent->OnDeath.AddUObject(this, &AMYBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &AMYBaseCharacter::OnHealthChanged);
}

void AMYBaseCharacter::OnHealthChanged(float Health)
{
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

// Called every frame
void AMYBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // TakeDamage(0.1f, FDamageEvent(), nullptr, this);
}

// Called to bind functionality to input
void AMYBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &AMYBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveSide", this, &AMYBaseCharacter::MoveSide);
    PlayerInputComponent->BindAxis("LookUp", this, &AMYBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &AMYBaseCharacter::AddControllerYawInput);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMYBaseCharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMYBaseCharacter::StopJumping);
    PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMYBaseCharacter::BeginCrouch);
    PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMYBaseCharacter::EndCrouch);
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMYBaseCharacter::BeginSprint);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMYBaseCharacter::EndSprint);
}

void AMYBaseCharacter::MoveForward(float Amount)
{
    if (Amount != 0.0f)
    {
        const FVector ForwardVector = GetActorForwardVector();
        AddMovementInput(ForwardVector, Amount);
    }
}

void AMYBaseCharacter::MoveSide(float Amount)
{
    if (Amount != 0.0f)
    {
        const FVector RightVector = GetActorRightVector();
        AddMovementInput(GetActorRightVector(), Amount);
    }
}

void AMYBaseCharacter::BeginSprint()
{
    GetCharacterMovement()->MaxWalkSpeed = 1200.0f;
}

void AMYBaseCharacter::EndSprint()
{
    GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void AMYBaseCharacter::BeginCrouch()
{
    Crouch();
}

void AMYBaseCharacter::EndCrouch()
{
    UnCrouch();
}

void AMYBaseCharacter::OnDeath()
{
    UE_LOG(LogBaseCharacter, Display, TEXT("Player %s is dead"), *GetName());

    // Playing death animation
    PlayAnimMontage(DeathAnimMontage);

    // Disabling movement of our character
    GetCharacterMovement()->DisableMovement();

    // Destroying our character
    SetLifeSpan(5.0f);
}
