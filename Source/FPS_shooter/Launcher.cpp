// Fill out your copyright notice in the Description page of Project Settings.


#include "Launcher.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

ALauncher::ALauncher()
{
}

void ALauncher::PullTrigger()
{
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();
	UGameplayStatics::SpawnSoundAtLocation(this, LaunchSound, GetActorLocation(), GetActorRotation());
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);
	
}
