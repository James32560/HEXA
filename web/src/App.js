import React, { useState, useEffect } from 'react';
import { Box, Slider } from '@mui/material';
import Joystick from 'rc-joystick';

import Container from './components/Container';
import ConnectButton from './components/ConnectButton';
import VerticalSlider from './components/Slider';
import './styles/App.css';

const App = () =>
{
    const [joystickDir, joystickDis] = [0, 0];

    return (
        <Box padding='20px' display='flex' flexDirection='column' gap='20px'>
            <ConnectButton/>
            <Box display='flex' flexDirection='row' gap='20px'>
                <Container><Joystick baseRadius={100}/></Container>
                <Container>
                    <VerticalSlider/>
                    <VerticalSlider/>
                </Container>
            </Box>
            <Box display='flex' gap='20px'>
                <Container>
                    <h1>Container 1</h1>
                </Container>
            </Box>
        </Box>
    );
} 

export default App;
