class ACEGVAR(medical_treatment,actions) {
    class BasicBandage;
    class Splint;
    class Morphine;
    class SurgicalKit;
    class CheckResponse;
    class CheckDogTags: CheckResponse {
        displayName = ACECSTRING(dogtags,checkItem);
        displayNameProgress = "";
        icon = QACEPATHTOF(dogtags,data\dogtag_icon_ca.paa);
        treatmentTime = 0.01;
        allowSelfTreatment = 1;
        condition = QFUNC(canCheckDogtag);
        callbackSuccess = QACEFUNC(dogtags,checkDogtag);
    };

    class PressureBandage: BasicBandage {
        displayName = "Pressure Bandage";
        displayNameProgress = ACECSTRING(medical_treatment,Bandaging);
        icon = QACEPATHTOF(medical_gui,ui\bandage.paa);
        category = "bandage";

        consumeItem = 1;
        items[] = {"ACM_PressureBandage"};

        medicRequired = 0;
        allowSelfTreatment = 1;
        allowedSelections[] = {"All"};
        treatmentLocations = TREATMENT_LOCATIONS_ALL;

        treatmentTime = QEFUNC(damage,getBandageTime);

        callbackStart = "";
        callbackProgress = "";
        callbackSuccess = QACEFUNC(medical_treatment,bandage);
        callbackFailure = "";

        animationMedic = "AinvPknlMstpSlayW[wpn]Dnon_medicOther";
        animationMedicProne = "AinvPpneMstpSlayW[wpn]Dnon_medicOther";
        animationMedicSelf = "AinvPknlMstpSlayW[wpn]Dnon_medic";
        animationMedicSelfProne = "AinvPpneMstpSlayW[wpn]Dnon_medic";
    };
    class EmergencyTraumaDressing: PressureBandage {
        displayName = "Emergency Trauma Dressing";
        items[] = {"ACM_EmergencyTraumaDressing"};
        allowSelfTreatment = 0;
    };
    class ElasticWrap: PressureBandage {
        displayName = "Wrap Bruises";
        displayNameProgress = "Wrapping...";
        items[] = {"ACM_ElasticWrap"};
        medicRequired = 1;
        condition = QUOTE([ARR_4(_medic,_patient,_bodyPart,2)] call EFUNC(damage,canWrap));
        treatmentTime = QEFUNC(damage,getBruiseWrapTime);
        callbackSuccess = QEFUNC(damage,wrapBruises);
    };
    class ElasticWrapBandages: ElasticWrap {
        displayName = "Wrap Bandaged Wounds";
        condition = QUOTE([ARR_3(_medic,_patient,_bodyPart)] call EFUNC(damage,canWrap));
        treatmentTime = QUOTE([ARR_4(_medic,_patient,_bodyPart,0)] call EFUNC(damage,getWrapTime));
        callbackSuccess = QUOTE([ARR_4(_medic,_patient,_bodyPart,0)] call EFUNC(damage,wrapBodypart));
    };
    /*class ElasticWrapClots: ElasticWrap {
        displayName = "";
        condition = QUOTE([ARR_4(_medic,_patient,_bodyPart,1)] call FUNC(canWrap));
        treatmentTime = QUOTE([ARR_4(_medic,_patient,_bodyPart,1)] call FUNC(getWrapTime));
        callbackSuccess = QUOTE([ARR_4(_medic,_patient,_bodyPart,1)] call FUNC(wrapBodypart));
    };*/
    class ElasticWrapSplint: ElasticWrap {
        displayName = "Wrap SAM Splint";
        allowedSelections[] = {"LeftArm","RightArm","LeftLeg","RightLeg"};
        condition = QEFUNC(disability,canWrapSplint);
        treatmentTime = QEFUNC(disability,getSplintWrapTime);
        callbackSuccess = QEFUNC(disability,wrapSplint);
    };
    class ApplySAMSplint: Splint {
        displayName = "Apply SAM Splint";
        displayNameProgress = "Applying SAM Splint...";
        items[] = {"ACM_SAMSplint"};
        allowedSelections[] = {"LeftArm","RightArm","LeftLeg","RightLeg"};
        condition = QACEFUNC(medical_treatment,canSplint);
        treatmentTime = QGVAR(treatmentTimeSAMSplint);
        callbackSuccess = QEFUNC(disability,splint);
    };
    class RemoveSAMSplint: Splint {
        displayName = "Remove SAM Splint";
        displayNameProgress = "Removing SAM Splint...";
        allowedSelections[] = {"LeftArm","RightArm","LeftLeg","RightLeg"};
        items[] = {};
        condition = QEFUNC(disability,canRemoveSplint);
        treatmentTime = 3;
        callbackSuccess = QEFUNC(disability,removeSplint);
        litter[] = {};
    };
    /*class ChitosanInjector: Morphine {
        displayName = CSTRING(ChitosanInjector_Display);
        displayNameProgress = CSTRING(ChitosanInjector_Progress);
        icon = QACEPATHTOF(medical_gui,ui\auto_injector.paa);
        category = "bandage";
        allowedSelections[] = {"All"};
        items[] = {"ACM_chitosanInjector"};
        condition = QUOTE([ARR_2(_patient,_bodyPart)] call FUNC(isBodyPartBleeding));
        callbackSuccess = QFUNC(applyChitosanInjector);
        litter[] = {};
    };*/
    class StitchWrappedWounds: SurgicalKit {
        displayName = "Use Surgical Kit (Wrapped)";
        treatmentTime = QUOTE([ARR_3(_patient,_bodyPart,1)] call EFUNC(damage,getStitchTime));
        condition = QUOTE([ARR_3(_medic,_patient,_bodyPart)] call EFUNC(damage,canStitch));
        callbackProgress = QUOTE([ARR_4(_args,_elapsedTime,_totalTime,1)] call EFUNC(damage,surgicalKitProgress));
    };
    /*class StitchClottedWounds: SurgicalKit {
        displayName = CSTRING(UseSurgicalKit_Clotted);
        treatmentTime = QUOTE([ARR_3(_patient,_bodyPart,2)] call FUNC(getStitchTime));
        condition = QUOTE([ARR_4(_medic,_patient,_bodyPart,1)] call FUNC(canStitch));
        callbackProgress = QUOTE([ARR_4(_args,_elapsedTime,_totalTime,2)] call FUNC(surgicalKitProgress));
    };*/

    class ApplyTourniquet;
    class RemoveTourniquet: ApplyTourniquet {
        treatmentTime = QGVAR(treatmentTimeTakeOffTourniquet);
    };

    // Medication

    class Paracetamol: Morphine {
        displayName = "Give Paracetamol";
        displayNameProgress = "Giving Paracetamol...";
        //icon = QACEPATHTOF(medical_gui,ui\auto_injector.paa);
        allowedSelections[] = {"Head"};
        items[] = {"ACM_Paracetamol"};
        condition = QUOTE([_patient] call ACEFUNC(common,isAwake));
        //treatmentTime = QACEGVAR(medical_treatment,treatmentTimeAutoinjector);
        //animationMedic = "AinvPknlMstpSnonWnonDnon_medic1";
        sounds[] = {};
        litter[] = {};
    };
    class Penthrox: Paracetamol {
        displayName = "Use Penthrox Inhaler";
        displayNameProgress = "Using Penthrox Inhaler";
        items[] = {"ACM_Inhaler_Penthrox"};
        animationMedic = "";
        //sounds[] = {};
    };
    class AmmoniaInhalant: Paracetamol {
        displayName = "Give Ammonia Inhalant";
        displayNameProgress = "Giving Ammonia Inhalant...";
        items[] = {"ACM_AmmoniaInhalant"};
        condition = QUOTE(([_patient] call ACEFUNC(common,isAwake)));
    };
    class Naloxone: Paracetamol {
        displayName = "Use Naloxone Spray";
        displayNameProgress = "Using Naloxone Spray...";
        items[] = {"ACM_Spray_Naloxone"};
        condition = "true";
        //sounds[] = {};
    };
    
    // Vials

    class Epinephrine_Vial: Morphine {
        displayName = "Push Epinephrine (Vial)";
        displayNameProgress = "Pushing Epinephrine...";
        //icon = QACEPATHTOF(medical_gui,ui\auto_injector.paa);
        allowedSelections[] = {"Body", "LeftArm", "RightArm", "LeftLeg", "RightLeg"};
        items[] = {"ACM_Vial_Epinephrine"};
        condition = QUOTE([ARR_2(_patient,_bodyPart)] call EFUNC(circulation,hasIV));
        //treatmentTime = QACEGVAR(medical_treatment,treatmentTimeAutoinjector);
        callbackSuccess = QACEFUNC(medical_treatment,medication);
        //animationMedic = "AinvPknlMstpSnonWnonDnon_medic1";
        sounds[] = {};
        litter[] = {};
    };
    class Morphine_Vial: Epinephrine_Vial {
        displayName = "Push Morphine (Vial)";
        displayNameProgress = "Pushing Morphine...";
        items[] = {"ACM_Vial_Morphine"};
    };
    class Adenosine_Vial: Epinephrine_Vial {
        displayName = "Push Adenosine (Vial)";
        displayNameProgress = "Pushing Adenosine...";
        items[] = {"ACM_Vial_Adenosine"};
    };
    class Amiodarone_Vial: Epinephrine_Vial {
        displayName = "Push Amiodarone (Vial)";
        displayNameProgress = "Pushing Amiodarone...";
        items[] = {"ACM_Vial_Amiodarone"};
    };
    class TXA_Vial: Epinephrine_Vial {
        displayName = "Push TXA (Vial)";
        displayNameProgress = "Pushing TXA...";
        items[] = {"ACM_Vial_TXA"};
    };
};
