import React from "react";
import { Slider } from "@mui/material";

const VerticalSlider = () =>
{
    const getAriaValueText = (value) => `${value}%`;

    return (
        <Slider
            orientation="vertical"
            defaultValue={50}
            valueLabelDisplay="auto"
            getAriaValueText={getAriaValueText} 
            sx={{height: 200, paddingLeft: 4, paddingRight: 4}}
        />);
};

export default VerticalSlider;
