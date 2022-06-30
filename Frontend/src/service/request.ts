import axios, { AxiosResponse } from "axios";
import qs from 'qs';

const baseURL = "/";

const instance = axios.create({
    baseURL,
    withCredentials: true,
    headers: {
        'Content-Type': 'application/x-www-form-urlencoded'
    }
});

instance.interceptors.request.use(
    config => ({ ...config, data: qs.stringify(config.data) }),
    error => Promise.reject(error)
)

const get = async <T>(url: string, params?: unknown): Promise<AxiosResponse<Resp<T>>> => {
    return await instance.get<Resp<T>>(url, { params });
}

const post = async <T>(url: string, data?: unknown): Promise<AxiosResponse<Resp<T>>> => {
    return await instance.post<Resp<T>>(url, data);
}

const upload = async <T>(
    url: string,
    blob: Blob,
    onUploadProgress?: (progressEvent: ProgressEvent) => void
): Promise<AxiosResponse<Resp<T>>> => {
    const data = new FormData();
    data.append('file', blob);
    return axios({
        method: "post",
        baseURL,
        url,
        data,
        onUploadProgress,
        withCredentials: true
    });
}

export { get, post, upload };

export default instance;