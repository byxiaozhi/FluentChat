import AppBar from '@mui/material/AppBar';
import Box from '@mui/material/Box';
import Toolbar from '@mui/material/Toolbar';
import Typography from '@mui/material/Typography';
import Menu from '@mui/material/Menu';
import Container from '@mui/material/Container';
import ExpandMoreIcon from '@mui/icons-material/ExpandMore';
import MenuItem from '@mui/material/MenuItem';
import React, { useEffect } from "react";
import { useAppSelector } from '../../service/store';
import { useNavigate } from "react-router-dom";
import { SxProps, Theme } from '@mui/material';
import { AppBarButton } from '../Button';
import { loadUserInfo, logoutUser } from 'src/service/user';

interface INavigationView {
    pages: IPageList;
    children: JSX.Element;
}

const ToolbarStyle: SxProps<Theme> = {
    display: 'flex'
}

const ToolbarItemStyle: SxProps<Theme> = {
    mx: 1,
    color: 'black',
    display: 'flex',
    alignItems: 'center'
};

const AppBarStyle: SxProps<Theme> = {
    display: 'fixed',
    backgroundColor: '#fff1',
    boxShadow: 'inset 0px -1px 1px #e7ebf0;',
    borderBottom: '#FFFFFF12',
    backdropFilter: 'blur(20px)'
}

const NavigationView: React.FC<INavigationView> = (props) => {
    const [anchorElUser, setAnchorElUser] = React.useState<Element>();
    const user = useAppSelector(e => e.user);
    const navigate = useNavigate();

    const handleOpenUserMenu = (event: React.MouseEvent<HTMLButtonElement, MouseEvent>) => {
        setAnchorElUser(event.currentTarget);
    };

    const handleCloseUserMenu = (f?: () => void) => {
        setAnchorElUser(undefined);
        f?.();
    };

    useEffect(() => {
        loadUserInfo();
    }, [])

    return (
        <>
            <AppBar sx={AppBarStyle}>
                <Container maxWidth="xl">
                    <Toolbar sx={ToolbarStyle}>
                        <Box sx={{ flexGrow: 1, display: 'flex' }}>
                            <Typography variant="h6" sx={{ ...ToolbarItemStyle, mr: 4 }}>
                                Fluent Chat
                            </Typography>
                            {props.pages.filter(e => !e.auth || e.auth(user?.role)).map(e => (
                                <AppBarButton key={e.path} sx={ToolbarItemStyle} onClick={() => navigate(e.path)}>
                                    {e.title}
                                </AppBarButton>
                            ))}
                        </Box>
                        {user.isLogin == true && <Box sx={{ flexGrow: 0 }}>
                            <AppBarButton onClick={handleOpenUserMenu} sx={ToolbarItemStyle}>
                                {user.username}<ExpandMoreIcon />
                            </AppBarButton>
                            <Menu
                                sx={{ mt: '45px' }}
                                anchorEl={anchorElUser}
                                anchorOrigin={{
                                    vertical: 'top',
                                    horizontal: 'right',
                                }}
                                keepMounted
                                transformOrigin={{
                                    vertical: 'top',
                                    horizontal: 'right',
                                }}
                                open={Boolean(anchorElUser)}
                                onClose={() => handleCloseUserMenu()}
                            >
                                <MenuItem onClick={() => {
                                    navigate('/')
                                    handleCloseUserMenu(logoutUser)
                                }}><Typography textAlign="center">退出登录</Typography>
                                </MenuItem>
                            </Menu>
                        </Box>}
                        {user.isLogin == false && <Box sx={{ flexGrow: 0, display: 'flex' }}>
                            <AppBarButton sx={ToolbarItemStyle} onClick={() => navigate('/login')}>
                                登录
                            </AppBarButton>
                        </Box>}
                    </Toolbar>
                </Container>
            </AppBar >
            <Container maxWidth="xl" sx={{ my: 10 }}>
                {props.children}
            </Container>
        </>
    )
}

export default NavigationView;