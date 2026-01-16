// FootballBall.cpp
#include "FootballBall.h"
#include "FootballCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AFootballBall::AFootballBall()
{
    PrimaryActorTick.bCanEverTick = false;

    // Collision sphere
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    CollisionComponent->InitSphereRadius(15.f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AFootballBall::OnBallOverlap);
    RootComponent = CollisionComponent;

    // Ball mesh
    BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
    BallMesh->SetupAttachment(CollisionComponent);
    BallMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    // Projectile movement
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->InitialSpeed = 0.f;
    ProjectileMovement->MaxSpeed = 3000.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->ProjectileGravityScale = 0.5f;
    ProjectileMovement->SetActive(false);

    HandSocketName = FName("Hand_R");
}

void AFootballBall::BeginPlay()
{
    Super::BeginPlay();
}

void AFootballBall::ThrowBall(FVector Velocity)
{
    ProjectileMovement->Velocity = Velocity;
    ProjectileMovement->SetActive(true);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    UE_LOG(LogTemp, Log, TEXT("Ball thrown with velocity: %s"), *Velocity.ToString());
}

void AFootballBall::AttachToCharacter(AFootballCharacter* Character)
{
    if (!Character)
    {
        return;
    }

    ProjectileMovement->SetActive(false);
    ProjectileMovement->Velocity = FVector::ZeroVector;
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    // Try to attach to hand socket, fallback to root
    USkeletalMeshComponent* CharacterMesh = Character->GetMesh();
    if (CharacterMesh && CharacterMesh->DoesSocketExist(HandSocketName))
    {
        AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, HandSocketName);
    }
    else
    {
        AttachToActor(Character, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
    }

    UE_LOG(LogTemp, Log, TEXT("Ball attached to character: %s"), *Character->GetName());
}

void AFootballBall::ResetBall()
{
    ProjectileMovement->SetActive(false);
    ProjectileMovement->Velocity = FVector::ZeroVector;
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AFootballBall::OnBallOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                  bool bFromSweep, const FHitResult& SweepResult)
{
    if (!ProjectileMovement->IsActive())
    {
        return; // Ball not in flight
    }

    AFootballCharacter* Character = Cast<AFootballCharacter>(OtherActor);
    if (!Character)
    {
        return;
    }

    // Find previous ball carrier and clear their flag
    TArray<AActor*> FoundCharacters;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFootballCharacter::StaticClass(), FoundCharacters);
    for (AActor* Actor : FoundCharacters)
    {
        AFootballCharacter* FC = Cast<AFootballCharacter>(Actor);
        if (FC && FC->HasBall())
        {
            FC->SetHasBall(false);
        }
    }

    // Attach to new character
    AttachToCharacter(Character);
    Character->SetHasBall(true);

    UE_LOG(LogTemp, Log, TEXT("Ball caught by: %s"), *Character->GetName());
}
