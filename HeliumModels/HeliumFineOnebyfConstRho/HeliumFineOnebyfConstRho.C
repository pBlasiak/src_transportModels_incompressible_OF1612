/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2015 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "HeliumFineOnebyfConstRho.H"
#include "addToRunTimeSelectionTable.H"
#include "surfaceFields.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace HeliumModels
{
    defineTypeNameAndDebug(HeliumFineOnebyfConstRho, 0);

    addToRunTimeSelectionTable
    (
        HeliumModel,
        HeliumFineOnebyfConstRho,
        dictionary
    );

	const Foam::label
	Foam::HeliumModels::HeliumFineOnebyfConstRho::largeIndex_(6672);

	const Foam::dimensionedScalar
	Foam::HeliumModels::HeliumFineOnebyfConstRho::dTFineOnebyf_("dTFineOnebyf", dimTemperature, 0.0001);

	#include "fineOnebyf.H"
}
}


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

//void Foam::HeliumModels::HeliumFineOnebyfConstRho::fineOnebyf()
//{
//	forAll(T_, celli)
//	{
//		if (T_[celli] < TMin_.value())
//		{
//			onebyf_[celli] = fineOnebyfTable_[indexMin_];
//		}
//		else if (T_[celli] > TMax_.value())
//		{
//			onebyf_[celli] = fineOnebyfTable_[largeIndex_];
//		}
//		else
//		{
//			label index = (T_[celli] - TMin_.value())/dTFineOnebyf_;
//			if (index == largeIndex_)
//			{
//				onebyf_[celli] = fineOnebyfTable_[largeIndex_];
//			}
//			else
//			{
//				scalar Ti1 = TMin_.value() + index*dTFineOnebyf_;
//				scalar Ti2 = Ti1 + dTFineOnebyf_;
//				scalar a = (fineOnebyfTable_[index + 1] - fineOnebyfTable_[index])/(Ti2 - Ti1);
//				scalar b = fineOnebyfTable_[index] - a*Ti1;
//				onebyf_[celli] =  a*T_[celli] + b;
//			}
//		}
//	}
//
//	forAll(T_.boundaryField(), patchi)
//	{
//		forAll(T_.boundaryField()[patchi], i)
//		{
//			if (T_.boundaryField()[patchi][i] < TMin_.value())
//			{
//				onebyf_.boundaryFieldRef()[patchi][i] = fineOnebyfTable_[indexMin_];
//			}
//			else if (T_.boundaryField()[patchi][i] > TMax_.value())
//			{
//				onebyf_.boundaryFieldRef()[patchi][i] = fineOnebyfTable_[largeIndex_];
//			}
//			else
//			{
//				label index = (T_.boundaryField()[patchi][i] - TMin_.value())/dTFineOnebyf_;
//				if (index == largeIndex_)
//				{
//					onebyf_.boundaryFieldRef()[patchi][i] = fineOnebyfTable_[largeIndex_];
//				}
//				else
//				{
//					scalar Ti1 = TMin_.value() + index*dTFineOnebyf_;
//					scalar Ti2 = Ti1 + dTFineOnebyf_;
//					scalar a = (fineOnebyfTable_[index + 1] - fineOnebyfTable_[index])/(Ti2 - Ti1);
//					scalar b = fineOnebyfTable_[index] - a*Ti1;
//					onebyf_.boundaryFieldRef()[patchi][i] =  a*T_.boundaryField()[patchi][i] + b;
//				}
//			}
//		}
//	}
//}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::HeliumModels::HeliumFineOnebyfConstRho::HeliumFineOnebyfConstRho
(
    const word& name,
    const dictionary& HeliumProperties,
    const volVectorField& U,
    const surfaceScalarField& phi
)
:
    HeliumConstRho(name, HeliumProperties, U, phi)
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void Foam::HeliumModels::HeliumFineOnebyfConstRho::correct()
{
	Info<< "HeliumFineOnebyfConstRho updates thermal properties..." << endl;
	nu_ = calcNu();
	calcHeProp(betaHe_, betaHeTable_, T_);
	calcHeProp(AGMHe_, AGMHeTable_, T_);
	calcHeProp(sHe_, sHeTable_, T_);
	calcHeProp(cpHe_, cpHeTable_, T_);
	calcHeProp(onebyf_, fineOnebyfTable_, T_, largeIndex_, dTFineOnebyf_);
}


// ************************************************************************* //
