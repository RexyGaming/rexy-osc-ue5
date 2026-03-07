#include "RexyOSCActor.h"
#include "RexyOSC2.h"
#include "OSCManager.h"
#include "OSCMessage.h"
#include "OSCAddress.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

ARexyOSCActor::ARexyOSCActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ARexyOSCActor::BeginPlay()
{
    Super::BeginPlay();

    if (!TargetCamera)
    {
        TArray<AActor*> FoundActors;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);
        for (AActor* Actor : FoundActors)
        {
            if (Actor->GetName().Contains(TEXT("CineCamera")))
            {
                TargetCamera = Actor;
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("RexyOSC: Found camera!"));
                break;
            }
        }
        if (!TargetCamera)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("RexyOSC: Could not find camera!"));
        }
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("RexyOSC: Camera reference is set!"));
    }

    OSCServer = UOSCManager::CreateOSCServer(TEXT("0.0.0.0"), 8000, false, true, TEXT("RexyOSCServer"), GetWorld());

    if (OSCServer)
    {
        OSCServer->OnOscMessageReceived.AddDynamic(this, &ARexyOSCActor::OnOSCMessageReceived);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("RexyOSC: Server started on port 8000"));
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("RexyOSC: FAILED to start server"));
    }

    if (TargetCamera)
    {
        APlayerController* PC = GetWorld()->GetFirstPlayerController();
        if (PC)
        {
            PC->SetViewTarget(TargetCamera);
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("RexyOSC: Camera view set"));
        }
    }
}

void ARexyOSCActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (OSCServer)
    {
        OSCServer->Stop();
    }
    Super::EndPlay(EndPlayReason);
}

void ARexyOSCActor::OnOSCMessageReceived(const FOSCMessage& Message, const FString& IPAddress, int32 Port)
{
    FOSCAddress OSCAddr = UOSCManager::GetOSCMessageAddress(Message);
    FString Address = OSCAddr.GetFullPath();

    float Value = 0.f;
    UOSCManager::GetFloat(Message, 0, Value);

    if (Address == TEXT("/rexy/wheels/pan"))
    {
        CurrentPan = Value;
    }
    else if (Address == TEXT("/rexy/wheels/tilt"))
    {
        CurrentTilt = Value;
    }

    if (TargetCamera)
    {
        FRotator NewRotation(CurrentTilt, CurrentPan, 0.f);
        TargetCamera->SetActorRotation(NewRotation);
    }
}
