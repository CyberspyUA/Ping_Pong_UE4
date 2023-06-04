// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardPawn.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ABoardPawn::ABoardPawn()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	Scene->SetupAttachment(RootComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(StaticMesh);
	CameraBoom->TargetArmLength = 100.f;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	MoveRate = 100;
}

void ABoardPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABoardPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoardPawn::Client_MoveLeftRight_Implementation(float Value) {
	FVector Location = this->GetActorLocation();
	FVector RightVector = this->GetActorRightVector();

	this->SetActorLocation(Location + RightVector * Value * MoveRate, true);

	//Output Players location
	/*GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("%s"), *GetActorLocation().ToString()));*/
}

void ABoardPawn::Multicast_MoveLeftRight_Implementation(float Value) {
	Client_MoveLeftRight(Value);
}

void ABoardPawn::Server_MoveLeftRight_Implementation(float Value) {
	Multicast_MoveLeftRight(Value);
}