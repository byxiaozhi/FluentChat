import { createSlice, PayloadAction } from '@reduxjs/toolkit'

interface IUserInfo {
    username: string,
    email: string,
    role: string
}

interface IUser extends Partial<IUserInfo> {
    isLogin?: boolean
}

const initialState: IUser = {};

export const configSlice = createSlice({
    name: 'user',
    initialState,
    reducers: {
        setUser: (state, action: PayloadAction<IUserInfo | undefined>) => {
            if (action.payload)
                return { isLogin: true, ...action.payload };
            return { isLogin: false };
        },
    }
});

export const { setUser } = configSlice.actions;
export type { IUserInfo, IUser }
export default configSlice.reducer;