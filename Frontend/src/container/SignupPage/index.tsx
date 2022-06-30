import { Button, Paper, Stack, SxProps, TextField, Theme, Typography, Container, Link, Alert } from "@mui/material";
import React, { useEffect, useState } from "react";
import { useNavigate } from "react-router";
import { loadUserInfo, signupUser } from "src/service/user";
import { handleValueChange } from "src/utility/common";

const SignupPaperStyle: SxProps<Theme> = {
    maxWidth: 350,
    margin: '0 auto',
    padding: 4,
    display: 'flex',
    flexDirection: 'column'
}

const SignupPage: React.FC = () => {
    const [nickname, setnickname] = useState('');
    const [email, setEmail] = useState('');
    const [password, setPassword] = useState('');
    const [helperText, setHelperText] = useState({ nickname: '', email: '', password: '' });


    const [errmsg, setErrmsg] = useState('');
    const navigate = useNavigate();

    const handleSignup = async () => {
        const ret = await signupUser(nickname, email, password);
        if (ret.code == 0)
            navigate('/login');
        else if (ret.data)
            ret.data.forEach(x => setHelperText(old => ({ ...old, [x.field]: x.message })))
        else
            setErrmsg(ret.message)
    }

    useEffect(() => {
        setErrmsg('')
    }, [nickname, email, password])

    useEffect(() => {
        setHelperText(old => ({ ...old, nickname: '' }))
    }, [nickname])

    useEffect(() => {
        setHelperText(old => ({ ...old, email: '' }))
    }, [email])

    useEffect(() => {
        setHelperText(old => ({ ...old, password: '' }))
    }, [password])

    return (
        <Container sx={{ pt: 10 }}>
            <Paper elevation={3} sx={SignupPaperStyle}>
                <Stack spacing={4} sx={{ mb: 2 }}>
                    <Typography variant="h5" sx={{ textAlign: 'center' }}>
                        注册
                    </Typography>
                    <TextField
                        error={!!helperText['nickname']}
                        helperText={helperText['nickname']}
                        label="昵称"
                        value={nickname}
                        onChange={handleValueChange(setnickname)} />
                    <TextField
                        error={!!helperText['email']}
                        helperText={helperText['email']}
                        label="电子邮箱"
                        value={email}
                        type={'email'}
                        onChange={handleValueChange(setEmail)} />
                    <TextField
                        error={!!helperText['password']}
                        helperText={helperText['password']}
                        label="密码"
                        value={password}
                        type={'password'}
                        onChange={handleValueChange(setPassword)} />
                </Stack>
                {errmsg && <Alert severity="error">{errmsg}</Alert>}
                <Button variant="contained" onClick={handleSignup} sx={{ mt: 2 }}>注册</Button>
                <Link textAlign={'center'} sx={{ pt: 2 }} href={'#/login'}>返回登录</Link>
            </Paper>
        </Container>
    )
}

export default SignupPage;