#include "..\script_component.hpp"
/*
 * Author: PabstMirror
 * Checks if AI healer has items.
 *
 * Arguments:
 * 0: Healer <OBJECT>
 * 1: Treatment Type <STRING>
 * 2: Target <OBJECT>
 *
 * Return Value:
 * 0: Has Item <BOOL>
 * 1: Item Classname <STRING> (Optional)
 * 2: Treatment <STRING> (Optional)
 *
 * Example:
 * [cursorObject, "@bandage"] call ace_medical_ai_fnc_itemCheck
 *
 * Public: No
 */

if (ACEGVAR(medical_ai,requireItems) == 0) exitWith { [true] };

params ["_healer", "_treatementType", ["_target", objNull]];

private _return = [false];
private _items = _healer call ACEFUNC(common,uniqueItems);
private _treatment = GVAR(itemHash) get _treatementType;
{
    if (_x in _items) exitWith {
        _return = [true, _x, _y];
    };
} forEach _treatment;

if !(isNull _target) then {
    private _targetItems = _target call ACEFUNC(common,uniqueItems);
    {
        if (_x in _targetItems) exitWith {
            _return = [true, _x, _y];
        };
    } forEach _treatment;
};

_return
