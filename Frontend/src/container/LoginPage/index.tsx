import { Button, Paper, Stack, SxProps, TextField, Theme, Typography, Container, Link, Alert } from "@mui/material";
import React, { useState } from "react";
import { useEffect } from "react";
import { useNavigate } from "react-router";
import { loadUserInfo, loginUser } from "src/service/user";
import { handleValueChange } from "src/utility/common";

const LoginPaperStyle: SxProps<Theme> = {
    maxWidth: 350,
    margin: '0 auto',
    padding: 4,
    display: 'flex',
    flexDirection: 'column'
}

const LoginPage: React.FC = () => {
    const [email, setEmail] = useState('');
    const [password, setPassword] = useState('');
    const [errmsg, setErrmsg] = useState('');
    const navigate = useNavigate();

    const handleLogin = async () => {
        const ret = await loginUser(email, password);
        if (ret.code == 0) {
            loadUserInfo();
            navigate('/')
        }
        else setErrmsg(ret.message)
    }

    useEffect(() => {
        setErrmsg('')
    }, [email, password])

    return (
        <Container sx={{ pt: 10 }}>
            <Paper elevation={3} sx={LoginPaperStyle}>
                <Stack spacing={4} sx={{ mb: 2 }}>
                    <Typography variant="h5" sx={{ textAlign: 'center' }}>
                        登录
                    </Typography>
                    <TextField label="电子邮箱" type={'email'} value={email} onChange={handleValueChange(setEmail)} />
                    <TextField label="密码" type={'password'} value={password} onChange={handleValueChange(setPassword)} />
                </Stack>
                {errmsg && <Alert severity="error">{errmsg}</Alert>}
                <Button variant="contained" onClick={handleLogin} sx={{ mt: 2 }}>登录</Button>
                <Link textAlign={'center'} sx={{ pt: 2 }} href={'#/signup'}>没有账号？立即注册</Link>
            </Paper>
        </Container>
    )
}
export default LoginPage;