format_version = "3.0"



custom_properties = jbox.property_set{
	document_owner = {
		properties = {
		  Detail1 = jbox.number {
		    property_tag = 11,
		    default = 0.05,
		    ui_name = jbox.ui_text("propertyname_Detail1"),
		    ui_type = jbox.ui_linear ({min=0, max=1, units={{decimals=2}}})
		  },
		  Detail2 = jbox.number {
        property_tag = 12,
        default = 1,
        ui_name = jbox.ui_text("propertyname_Detail2"),
        ui_type = jbox.ui_linear ({min=0, max=1, units={{decimals=2}}})
      },
      Detail3 = jbox.number {
        property_tag = 13,
        default = 1,
        ui_name = jbox.ui_text("propertyname_Detail3"),
        ui_type = jbox.ui_linear ({min=0, max=1, units={{decimals=2}}})
      },
      Detail4 = jbox.number {
        property_tag = 14,
        default = 1,
        ui_name = jbox.ui_text("propertyname_Detail4"),
        ui_type = jbox.ui_linear ({min=0, max=1, units={{decimals=2}}})
      },
      Approximation = jbox.number {
        property_tag = 15,
        default = 1,
        ui_name = jbox.ui_text("propertyname_Approximation"),
        ui_type = jbox.ui_linear ({min=0, max=1, units={{decimals=2}}})
      },
   Algorithm = jbox.number {
        property_tag = 16,
        default = 0,
        steps = 2,
        ui_name = jbox.ui_text("propertyname_Algorithm"),
        ui_type = jbox.ui_selector { jbox.ui_text("threshold"), jbox.ui_text("scale")},
      }
		}
	},
	rtc_owner = {
		properties = { instance = jbox.native_object{} }
	},
	rt_owner = {}

}

audio_inputs = {
  audioInL = jbox.audio_input{ ui_name = jbox.ui_text("audioInputL") },
  audioInR = jbox.audio_input{ ui_name = jbox.ui_text("audioInputR") },
}
audio_outputs = {
  audioOutL = jbox.audio_output{ ui_name = jbox.ui_text("audioOutputL") },
  audioOutR = jbox.audio_output{ ui_name = jbox.ui_text("audioOutputR") },
}

midi_implementation_chart = {
  midi_cc_chart = {
   [20] = "/custom_properties/Detail1",
   [21] = "/custom_properties/Detail2",
   [22] = "/custom_properties/Detail3",
   [23] = "/custom_properties/Detail4",
   [24] = "/custom_properties/Approximation",
   [25] = "/custom_properties/Algorithm"
  }
}



function remote_item(name)
  return {
    internal_name = name,
    short_ui_name = jbox.ui_text("short_"..name),
    shortest_ui_name = jbox.ui_text("shortest_"..name)
  }
end

remote_implementation_chart = {}
for n = 1,4 do
  remote_implementation_chart["/custom_properties/Detail"..n] = remote_item("Detail"..n)
end
remote_implementation_chart["/custom_properties/Approximation"] = remote_item("Approximation")
remote_implementation_chart["/custom_properties/Threshold"] = remote_item("Threshold")

jbox.add_stereo_effect_routing_hint{
  left_input = "/audio_inputs/audioInputL",
  right_input = "/audio_inputs/audioInputR",
  left_output = "/audio_outputs/audioOutputL",
  right_output = "/audio_outputs/audioOutputR",
  type = "true_stereo"
}
jbox.add_stereo_audio_routing_target{
  signal_type = "return",
  left = "/audio_inputs/audioInputL",
  right = "/audio_inputs/audioInputR",
  auto_route_enable = true
}
jbox.add_stereo_audio_routing_target{
  signal_type = "send",
  left = "/audio_outputs/audioOutputL",
  right = "/audio_outputs/audioOutputR",
  auto_route_enable = true
}
jbox.add_stereo_audio_routing_pair{
  left = "/audio_inputs/audioInputL",
  right = "/audio_inputs/audioInputR"
}
jbox.add_stereo_audio_routing_pair{
  left = "/audio_outputs/audioOutputL",
  right = "/audio_outputs/audioOutputR"
}
jbox.set_effect_auto_bypass_routing{
  {
    "/audio_inputs/audioInputL",
    "/audio_outputs/audioOutputL"
  },
  {
    "/audio_inputs/audioInputR",
    "/audio_outputs/audioOutputR"
  }
}







