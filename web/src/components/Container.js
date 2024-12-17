import React from 'react';
import { Box } from '@mui/material';

const Container = ({children, sx={}}) =>
{
    const styles =
    {
        display: 'flex',
        padding: 2,
        border: `2px solid gray`, '&:hover': {borderColor: '#007FFF'},
        borderRadius: '10px',
        justifyContent: 'center',
        alignItems: 'center',
    }

    return (<Box sx={{...styles, ...sx}}> {children} </Box>);
};

export default Container;
