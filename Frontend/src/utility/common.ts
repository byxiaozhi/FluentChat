const handleValueChange = (f: React.Dispatch<string>) =>
    (e: React.ChangeEvent<HTMLTextAreaElement>) => f(e.target.value);

const formatDate = (date: string) => new Date(date).toLocaleString("zh-cn")

export { handleValueChange, formatDate }