import { IUserInfo, setUser } from "src/model/user";
import { get, post } from "./request";
import store from "./store";

const loadUserInfo = async (): Promise<void> => {
    const { data } = await get("/api/user/info");
    if (data.code === 0)
        store.dispatch(setUser(data.data as IUserInfo));
    else
        store.dispatch(setUser(undefined));
}

const loginUser = async (email: string, password: string): Promise<Resp<string>> => {
    const ret = await post<string>("/api/user/login", { email, password, rememberMe: true });
    return ret.data;
}

const signupUser = async (nickname: string, email: string, password: string): Promise<Resp<FieldError[] | null>> => {
    const ret = await post<FieldError[] | null>("/api/user/signup", { nickname, email, password });
    return ret.data;
}

const logoutUser = async (): Promise<void> => {
    await get("/api/user/logout");
    loadUserInfo();
}

export { loadUserInfo, loginUser, signupUser, logoutUser };