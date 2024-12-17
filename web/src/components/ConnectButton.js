import React, { useState } from 'react';
import Button from '@mui/material/Button';

const ConnectButton = () =>
{
	const [isConnected, setIsConnected] = useState(false);
	const handleToggleConnection = () => {setIsConnected(!isConnected);};

	const styles =
	{
		backgroundColor: isConnected ? 'green' : 'red', '&:hover': {backgroundColor: isConnected ? 'darkgreen' : 'darkred'},
		width: 195,
	}

	return (
		<Button variant="contained" onClick={handleToggleConnection} sx={styles}>
			{isConnected ? 'Connected' : 'Not Connected'}
		</Button>
	);
};

export default ConnectButton;
