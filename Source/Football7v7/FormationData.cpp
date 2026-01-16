// FormationData.cpp
#include "FormationData.h"

UFormationData* UFormationData::CreateProFormation()
{
	UFormationData* Formation = NewObject<UFormationData>();
	Formation->FormationName = TEXT("Pro Formation");
	Formation->Team = ETeam::Offense;
	Formation->bIs11v11 = true;
	Formation->Description = TEXT("Balanced offense with RB in backfield");

	// Offensive Line (5 positions)
	Formation->PlayerSlots.Add({ EPosition::LT, FVector(0.f, -300.f, 0.f), FRotator::ZeroRotator });
	Formation->PlayerSlots.Add({ EPosition::LG, FVector(0.f, -150.f, 0.f), FRotator::ZeroRotator });
	Formation->PlayerSlots.Add({ EPosition::C, FVector(0.f, 0.f, 0.f), FRotator::ZeroRotator });
	Formation->PlayerSlots.Add({ EPosition::RG, FVector(0.f, 150.f, 0.f), FRotator::ZeroRotator });
	Formation->PlayerSlots.Add({ EPosition::RT, FVector(0.f, 300.f, 0.f), FRotator::ZeroRotator });

	// Quarterback
	Formation->PlayerSlots.Add({ EPosition::QB, FVector(-200.f, 0.f, 0.f), FRotator::ZeroRotator });

	// Running Back
	Formation->PlayerSlots.Add({ EPosition::RB, FVector(-300.f, 0.f, 0.f), FRotator::ZeroRotator });

	// Wide Receivers
	Formation->PlayerSlots.Add({ EPosition::WR1, FVector(0.f, -600.f, 0.f), FRotator::ZeroRotator });
	Formation->PlayerSlots.Add({ EPosition::WR2, FVector(0.f, 600.f, 0.f), FRotator::ZeroRotator });

	// Tight End
	Formation->PlayerSlots.Add({ EPosition::TE, FVector(0.f, 400.f, 0.f), FRotator::ZeroRotator });

	// Fullback (optional, can be swapped for WR3)
	Formation->PlayerSlots.Add({ EPosition::FB, FVector(-250.f, 50.f, 0.f), FRotator::ZeroRotator });

	return Formation;
}

UFormationData* UFormationData::CreateShotgunFormation()
{
	UFormationData* Formation = NewObject<UFormationData>();
	Formation->FormationName = TEXT("Shotgun Spread");
	Formation->Team = ETeam::Offense;
	Formation->bIs11v11 = true;
	Formation->Description = TEXT("QB in shotgun with spread receivers");

	// Offensive Line
	Formation->PlayerSlots.Add({ EPosition::LT, FVector(0.f, -300.f, 0.f), FRotator::ZeroRotator });
	Formation->PlayerSlots.Add({ EPosition::LG, FVector(0.f, -150.f, 0.f), FRotator::ZeroRotator });
	Formation->PlayerSlots.Add({ EPosition::C, FVector(0.f, 0.f, 0.f), FRotator::ZeroRotator });
	Formation->PlayerSlots.Add({ EPosition::RG, FVector(0.f, 150.f, 0.f), FRotator::ZeroRotator });
	Formation->PlayerSlots.Add({ EPosition::RT, FVector(0.f, 300.f, 0.f), FRotator::ZeroRotator });

	// Quarterback in shotgun
	Formation->PlayerSlots.Add({ EPosition::QB, FVector(-400.f, 0.f, 0.f), FRotator::ZeroRotator });

	// Running Back offset
	Formation->PlayerSlots.Add({ EPosition::RB, FVector(-400.f, -100.f, 0.f), FRotator::ZeroRotator });

	// Four Wide Receivers spread
	Formation->PlayerSlots.Add({ EPosition::WR1, FVector(0.f, -700.f, 0.f), FRotator::ZeroRotator });
	Formation->PlayerSlots.Add({ EPosition::WR2, FVector(0.f, -400.f, 0.f), FRotator::ZeroRotator });
	Formation->PlayerSlots.Add({ EPosition::WR3, FVector(0.f, 400.f, 0.f), FRotator::ZeroRotator });
	Formation->PlayerSlots.Add({ EPosition::TE, FVector(0.f, 700.f, 0.f), FRotator::ZeroRotator });

	return Formation;
}

UFormationData* UFormationData::Create43DefenseFormation()
{
	UFormationData* Formation = NewObject<UFormationData>();
	Formation->FormationName = TEXT("4-3 Defense");
	Formation->Team = ETeam::Defense;
	Formation->bIs11v11 = true;
	Formation->Description = TEXT("Four down linemen, three linebackers");

	// Defensive Line (4)
	Formation->PlayerSlots.Add({ EPosition::DE1, FVector(0.f, -400.f, 0.f), FRotator(0.f, 180.f, 0.f) });
	Formation->PlayerSlots.Add({ EPosition::DT1, FVector(0.f, -150.f, 0.f), FRotator(0.f, 180.f, 0.f) });
	Formation->PlayerSlots.Add({ EPosition::DT2, FVector(0.f, 150.f, 0.f), FRotator(0.f, 180.f, 0.f) });
	Formation->PlayerSlots.Add({ EPosition::DE2, FVector(0.f, 400.f, 0.f), FRotator(0.f, 180.f, 0.f) });

	// Linebackers (3)
	Formation->PlayerSlots.Add({ EPosition::OLB1, FVector(-200.f, -300.f, 0.f), FRotator(0.f, 180.f, 0.f) });
	Formation->PlayerSlots.Add({ EPosition::MLB, FVector(-200.f, 0.f, 0.f), FRotator(0.f, 180.f, 0.f) });
	Formation->PlayerSlots.Add({ EPosition::OLB2, FVector(-200.f, 300.f, 0.f), FRotator(0.f, 180.f, 0.f) });

	// Cornerbacks (2)
	Formation->PlayerSlots.Add({ EPosition::CB1, FVector(-100.f, -600.f, 0.f), FRotator(0.f, 180.f, 0.f) });
	Formation->PlayerSlots.Add({ EPosition::CB2, FVector(-100.f, 600.f, 0.f), FRotator(0.f, 180.f, 0.f) });

	// Safeties (2)
	Formation->PlayerSlots.Add({ EPosition::FS, FVector(-400.f, 0.f, 0.f), FRotator(0.f, 180.f, 0.f) });
	Formation->PlayerSlots.Add({ EPosition::SS, FVector(-400.f, 200.f, 0.f), FRotator(0.f, 180.f, 0.f) });

	return Formation;
}

UFormationData* UFormationData::Create34DefenseFormation()
{
	UFormationData* Formation = NewObject<UFormationData>();
	Formation->FormationName = TEXT("3-4 Defense");
	Formation->Team = ETeam::Defense;
	Formation->bIs11v11 = true;
	Formation->Description = TEXT("Three down linemen, four linebackers");

	// Defensive Line (3)
	Formation->PlayerSlots.Add({ EPosition::DE1, FVector(0.f, -300.f, 0.f), FRotator(0.f, 180.f, 0.f) });
	Formation->PlayerSlots.Add({ EPosition::DT1, FVector(0.f, 0.f, 0.f), FRotator(0.f, 180.f, 0.f) });
	Formation->PlayerSlots.Add({ EPosition::DE2, FVector(0.f, 300.f, 0.f), FRotator(0.f, 180.f, 0.f) });

	// Linebackers (4)
	Formation->PlayerSlots.Add({ EPosition::OLB1, FVector(-200.f, -400.f, 0.f), FRotator(0.f, 180.f, 0.f) });
	Formation->PlayerSlots.Add({ EPosition::MLB, FVector(-200.f, -100.f, 0.f), FRotator(0.f, 180.f, 0.f) });
	Formation->PlayerSlots.Add({ EPosition::OLB2, FVector(-200.f, 100.f, 0.f), FRotator(0.f, 180.f, 0.f) });
	Formation->PlayerSlots.Add({ EPosition::DT2, FVector(-200.f, 400.f, 0.f), FRotator(0.f, 180.f, 0.f) }); // Using DT2 as 4th LB

	// Cornerbacks (2)
	Formation->PlayerSlots.Add({ EPosition::CB1, FVector(-100.f, -600.f, 0.f), FRotator(0.f, 180.f, 0.f) });
	Formation->PlayerSlots.Add({ EPosition::CB2, FVector(-100.f, 600.f, 0.f), FRotator(0.f, 180.f, 0.f) });

	// Safeties (2)
	Formation->PlayerSlots.Add({ EPosition::FS, FVector(-400.f, 0.f, 0.f), FRotator(0.f, 180.f, 0.f) });
	Formation->PlayerSlots.Add({ EPosition::SS, FVector(-400.f, 200.f, 0.f), FRotator(0.f, 180.f, 0.f) });

	return Formation;
}
