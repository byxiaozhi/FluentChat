import { TypedUseSelectorHook, useDispatch, useSelector } from 'react-redux';
import { configureStore, Dispatch } from '@reduxjs/toolkit';
import configReducer from '../model/config';
import userReducer from '../model/user';

const store = configureStore({
  reducer: {
    config: configReducer,
    user: userReducer,
  }
})

export type RootState = ReturnType<typeof store.getState>
export const useAppDispatch = (): Dispatch => useDispatch<typeof store.dispatch>()
export const useAppSelector: TypedUseSelectorHook<RootState> = useSelector

export default store