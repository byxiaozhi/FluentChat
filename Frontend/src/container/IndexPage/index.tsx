import { Button, Paper, Stack, SxProps, TextField, Theme, Typography, Container, Link, Alert } from "@mui/material";
import React, { useEffect, useState } from "react";
import { useNavigate } from "react-router";

const IndexPage: React.FC = () => {
    return <Stack direction={'row'}>
        <Stack direction={'column'}>
            <h1>Fluent Chat: 一款即时聊天应用</h1>
            <h1>小组成员：</h1>
            <h2>55190630 朱志放</h2>
            <h2>55190715 刘轩赫</h2>
            <h2>55190711 范润浩</h2>
            <h2>55190613 刘浩斌</h2>
        </Stack>
        <img src='1.png' width={500} />
    </Stack>
}

export default IndexPage;