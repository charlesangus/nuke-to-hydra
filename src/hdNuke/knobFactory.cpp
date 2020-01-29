// Copyright 2019-present Nathan Rusch
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "knobFactory.h"

#include <pxr/base/gf/vec3f.h>
#include <pxr/base/gf/vec4f.h>


PXR_NAMESPACE_OPEN_SCOPE


Knob*
HdNukeKnobFactory::VtValueKnob(Knob_Callback f, const std::string& name,
                               const std::string& label, const VtValue& value)
{
    if (value.IsEmpty()) {
        return nullptr;
    }

    if (value.IsArrayValued()) {
        TF_WARN("Array value types are not currently supported for knob "
                "conversion: %s", value.GetTypeName().c_str());
        return nullptr;
    }

    Knob* knob = nullptr;

    // TODO: Vector types
    if (value.IsHolding<int>()) {
        int* data = _intKnobStorage.FindOrAllocate(name, value);
        knob = Int_knob(f, data, name.c_str(), label.c_str());
    }
    else if (value.IsHolding<float>()) {
        float* data = _floatKnobStorage.FindOrAllocate(name, value);
        knob = Float_knob(f, data, name.c_str(), label.c_str());
    }
    else if (value.IsHolding<double>()) {
        double* data = _doubleKnobStorage.FindOrAllocate(name, value);
        knob = Double_knob(f, data, name.c_str(), label.c_str());
    }
    else if (value.IsHolding<bool>()) {
        bool* data = _boolKnobStorage.FindOrAllocate(name, value);
        knob = Bool_knob(f, data, name.c_str(), label.c_str());
    }
    else if (value.IsHolding<std::string>()) {
        std::string* data = _stringKnobStorage.FindOrAllocate(name, value);
        knob = String_knob(f, data, name.c_str(), label.c_str());
    }
    else {
        TF_WARN("Unsupported value type for knob conversion: %s",
                value.GetTypeName().c_str());
    }
    return knob;
}

void
HdNukeKnobFactory::FreeDynamicKnobStorage()
{
    _intKnobStorage.Clear();
    _floatKnobStorage.Clear();
    _doubleKnobStorage.Clear();
    _boolKnobStorage.Clear();
    _stringKnobStorage.Clear();
}

/* static */
VtValue
HdNukeKnobFactory::KnobToVtValue(Knob* knob)
{
    if (not knob) {
        return VtValue();
    }

    switch(knob->ClassID()) {
        case FLOAT_KNOB:
            return VtValue(static_cast<float>(knob->get_value()));
        case DOUBLE_KNOB:
            return VtValue(knob->get_value());
        case BOOL_KNOB:
            return VtValue(static_cast<bool>(knob->get_value()));
        case INT_KNOB:
        case ENUMERATION_KNOB:
            return VtValue(static_cast<int>(knob->get_value()));
        case COLOR_KNOB:
        case XYZ_KNOB:
            return VtValue(GfVec3f(knob->get_value(0), knob->get_value(1),
                                   knob->get_value(2)));
        case ACOLOR_KNOB:
            return VtValue(GfVec4f(knob->get_value(0), knob->get_value(1),
                                   knob->get_value(2), knob->get_value(3)));
        case STRING_KNOB:
        case FILE_KNOB:
            return VtValue(knob->get_text());
        default:
            TF_WARN("KnobToVtValue : No VtValue conversion implemented for "
                    "knob type ID: %d", knob->ClassID());
            return VtValue();
    }
}

PXR_NAMESPACE_CLOSE_SCOPE
