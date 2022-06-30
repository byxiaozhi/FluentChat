import { useEffect, useState } from "react";

const useBreakpoints = (breakpoints: 'sm' | 'md' | 'lg' | 'xl' | 'xxl'): boolean => {
    const dimensions = { sm: 576, md: 768, lg: 992, xl: 1200, xxl: 1400 };
    const [width, setWidth] = useState(document.body.clientWidth);
    useEffect(() => {
        const fn = () => setWidth(document.body.clientWidth);
        addEventListener('resize', fn);
        return () => removeEventListener('resize', fn);
    }, []);
    return width >= dimensions[breakpoints];
}

const useLocalStorage = <T>(key: string, initialValue: T): readonly [T, React.Dispatch<React.SetStateAction<T>>] => {

    const [storedValue, setStoredValue] = useState<T>(() => {
        try {
            const item = window.localStorage.getItem(key);
            return item ? JSON.parse(item) : initialValue;
        } catch (error) {
            console.log(error);
            return initialValue;
        }
    });

    const setValue: React.Dispatch<React.SetStateAction<T>> = value => {
        try {
            const valueToStore = value instanceof Function ? value(storedValue) : value;
            setStoredValue(valueToStore);
            window.localStorage.setItem(key, JSON.stringify(valueToStore));
        } catch (error) {
            console.log(error);
        }
    };

    return [storedValue, setValue] as const;
}

export { useBreakpoints, useLocalStorage }