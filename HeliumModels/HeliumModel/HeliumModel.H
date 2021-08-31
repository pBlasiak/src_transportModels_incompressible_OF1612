/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
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

Namespace
    Foam::HeliumModels

Description
    A namespace for various incompressible HeliumModel implementations.

Class
    Foam::HeliumModel

Description
    An abstract base class for incompressible HeliumModels.

SourceFiles
    HeliumModel.C
    HeliumModelNew.C

\*---------------------------------------------------------------------------*/

#ifndef HeliumModel_H
#define HeliumModel_H

#include "dictionary.H"
#include "volFieldsFwd.H"
#include "surfaceFieldsFwd.H"
#include "dimensionedScalar.H"
#include "runTimeSelectionTables.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                Class HeliumModel Declaration
\*---------------------------------------------------------------------------*/

class HeliumModel
{

protected:

    // Protected data

        word name_;
        dictionary HeliumProperties_;

        const volVectorField& U_;
        const surfaceScalarField& phi_;



    // Private Member Functions

        //- Disallow copy construct
        HeliumModel(const HeliumModel&);

        //- Disallow default bitwise assignment
        void operator=(const HeliumModel&);


public:

    //- Runtime type information
    TypeName("HeliumModel");


    // Declare run-time constructor selection table

        declareRunTimeSelectionTable
        (
            autoPtr,
            HeliumModel,
            dictionary,
            (
                const word& name,
                const dictionary& HeliumProperties,
                const volVectorField& U,
                const surfaceScalarField& phi
            ),
            (name, HeliumProperties, U, phi)
        );


    // Selectors

        //- Return a reference to the selected Helium model
        static autoPtr<HeliumModel> New
        (
            const word& name,
            const dictionary& HeliumProperties,
            const volVectorField& U,
            const surfaceScalarField& phi
        );


    // Constructors

        //- Construct from components
        HeliumModel
        (
            const word& name,
            const dictionary& HeliumProperties,
            const volVectorField& U,
            const surfaceScalarField& phi
        );


    //- Destructor
    virtual ~HeliumModel()
    {}


    // Member Functions

        //- Return the helium properties dictionary
        const dictionary& HeliumProperties() const
        {
            return HeliumProperties_;
        }

        //- Return the laminar Helium
        virtual tmp<volScalarField> nu() const = 0;

        //- Return the laminar Helium for patch
        virtual tmp<scalarField> nu(const label patchi) const = 0;

        //- Correct the laminar Helium
        virtual void correct() = 0;

        //- Read transportProperties dictionary
        virtual bool read(const dictionary& HeliumProperties) = 0;

		//- Returns thermal expansion coefficient 
        virtual const volScalarField& beta() const = 0;

		//- Returns Goerter-Mellink coefficient 
        virtual const volScalarField& AGM() const = 0;

		//- Returns entropy 
        virtual const volScalarField& s() const = 0;

		//- Returns dynamic Helium 
        virtual const volScalarField& eta() const = 0;
	
		//- Returns specific heat capacity 
        virtual const volScalarField& cp() const = 0;

		//- Returns thermal conductivity function 
        virtual const volScalarField& kappa() const = 0;
		
        //- Returns the density
        virtual const volScalarField& rho() const = 0;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
