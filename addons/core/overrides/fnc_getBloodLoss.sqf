#include "..\script_component.hpp"
/*
 * Author: Glowbal
 * Calculate the total blood loss of a unit.
 *
 * Arguments:
 * 0: The Unit <OBJECT>
 *
 * Return Value:
 * Total blood loss of unit (litres/second) <NUMBER>
 *
 * Example:
 * [player] call ace_medical_status_fnc_getBloodLoss
 *
 * Public: No
 */

params ["_unit"];

private _woundBleeding = GET_WOUND_BLEEDING(_unit);
if (_woundBleeding == 0) exitWith {0};

private _cardiacOutput = [_unit] call ACEFUNC(medical_status,getCardiacOutput);
private _resistance = _unit getVariable [VAR_PERIPH_RES, DEFAULT_PERIPH_RES]; // can use value directly since this is sum of default and adjustments

// even if heart stops blood will still flow slowly (gravity)
private _bloodLoss = (_woundBleeding * (_cardiacOutput max EGVAR(circulation,cardiacArrestBleedRate)) * (DEFAULT_PERIPH_RES / _resistance) * ACEGVAR(medical,bleedingCoefficient));

private _eventArgs = [_unit, _bloodLoss]; // Pass by reference

[QACEGVAR(medical_status,getBloodLoss), _eventArgs] call CBA_fnc_localEvent;

_eventArgs select 1 // return