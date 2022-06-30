import React, { useCallback, useEffect, useState } from "react";
import { Box, Button, Checkbox, Container, Dialog, DialogActions, DialogContent, DialogContentText, DialogTitle, MenuItem, Pagination, Paper, Select, Stack, Table, TableBody, TableCell, TableContainer, TableHead, TableRow, TextField, Typography } from "@mui/material";
import { get, post } from "src/service/request";
import { handleValueChange } from "src/utility/common";

interface IUser {
    id: number
    username: string
    email: string
    role: string
}

const pageSize = 5;

const roleMap: Record<string, string> = { 'user': '普通用户', 'admin': '管理员' }

const UserManager: React.FC = () => {
    const [page, setPage] = useState(1)
    const [total, setTotal] = useState(0)
    const [data, setData] = useState<IUser[]>([])
    const [deleteDialog, setDeleteDialog] = useState<IUser>()
    const [editing, setEditing] = useState<IUser>()
    const [editRole, setEditRole] = useState('')
    const [query, setQuery] = useState('')

    const loadData = useCallback(async () => {
        const res = await get<{ list: IUser[], total: number }>('/api/user/list', { page: page - 1, count: pageSize, query })
        if (res.data.code == 0) {
            setData(res.data.data.list)
            setTotal(res.data.data.total)
        }
    }, [page, query]);

    const deleteUser = useCallback(async (user: IUser) => {
        const res = await post('/api/user/delete', { id: user.id })
        if (res.data.code == 0) {
            loadData()
        }
    }, [loadData])

    const editUser = useCallback((user: IUser) => {
        setEditRole(user.role)
        setEditing(user)
    }, [])

    const saveUser = useCallback(async () => {
        if (!editing) return;
        const res = await post('/api/user/editRole', { id: editing.id, role: editRole })
        if (res.data.code == 0) {
            await loadData()
        }
        setEditing(undefined)
    }, [editRole, editing, loadData])

    useEffect(() => {
        loadData()
    }, [loadData])


    return <Container sx={{ pt: 4 }}>
        <Stack gap={4} >
            <Typography variant="h4">
                用户管理
            </Typography>
            <Stack gap={2}>
                <Stack direction={'row'} gap={1}>
                    <TextField id="outlined-basic" label="筛选：用户名/邮箱" value={query} onChange={handleValueChange(setQuery)} variant="outlined" />
                </Stack>
                <TableContainer component={Paper}>
                    <Table>
                        <TableHead>
                            <TableRow>
                                <TableCell sx={{ width: 300 }}>用户名</TableCell>
                                <TableCell sx={{ width: 300 }}>邮箱</TableCell>
                                <TableCell sx={{ width: 300 }}>身份</TableCell>
                                <TableCell sx={{ width: 150 }}>操作</TableCell>
                            </TableRow>
                        </TableHead>
                        <TableBody>
                            {data.map(item => (
                                <TableRow key={item.id} sx={{ '&:last-child td, &:last-child th': { border: 0 } }}>
                                    <TableCell>
                                        {item.username}
                                    </TableCell>
                                    <TableCell>
                                        {item.email}
                                    </TableCell>
                                    <TableCell>
                                        {editing != item && <>
                                            {roleMap[item.role]}
                                        </>}
                                        {editing == item && <>
                                            <Select size="small" sx={{ margin: '-4px 0 -4px 0', width: 140 }} value={editRole} onChange={e => setEditRole(e.target.value)}>
                                                {Object.keys(roleMap).map(e => (
                                                    <MenuItem key={e} value={e}>{roleMap[e]}</MenuItem>
                                                ))}
                                            </Select>
                                        </>}
                                    </TableCell>
                                    <TableCell>
                                        <Stack direction={'row'}>
                                            {editing != item && <>
                                                <Button onClick={() => editUser(item)}>编辑</Button>
                                                <Button onClick={() => setDeleteDialog(item)} disabled={item.role == 'admin'}>删除</Button>
                                            </>}
                                            {editing == item && <>
                                                <Button onClick={saveUser}>保存</Button>
                                                <Button onClick={() => setEditing(undefined)}>取消</Button>
                                            </>}

                                        </Stack>
                                    </TableCell>
                                </TableRow>
                            ))}
                        </TableBody>
                    </Table>
                </TableContainer>
                <Pagination count={Math.ceil(total / pageSize)} page={page} onChange={(e, p) => setPage(p)} />
            </Stack>
        </Stack>

        <Dialog
            open={!!deleteDialog}
            onClose={() => setDeleteDialog(undefined)}
        >
            <DialogTitle>
                删除用户
            </DialogTitle>
            <DialogContent sx={{ minWidth: 300 }} >
                <DialogContentText>
                    确认删除“{deleteDialog?.username}”吗
                </DialogContentText>
            </DialogContent>
            <DialogActions>
                <Button onClick={() => {
                    deleteDialog && deleteUser(deleteDialog);
                    setDeleteDialog(undefined)
                }}>删除</Button>
                <Button onClick={() => setDeleteDialog(undefined)}>取消</Button>
            </DialogActions>
        </Dialog>
    </Container>
}

export default UserManager;