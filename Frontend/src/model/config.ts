import { createSlice, PayloadAction } from '@reduxjs/toolkit'

interface IConfig {
    theme: 'light' | 'dark',
    title: string
}

const initialState: IConfig = {
    theme: 'light',
    title: 'CellData'
}

export const configSlice = createSlice({
    name: 'config',
    initialState,
    reducers: {
        setTheme: (state, action: PayloadAction<typeof initialState.theme>) => {
            state.theme = action.payload;
        }
    }
});

export const { setTheme } = configSlice.actions;
export default configSlice.reducer;