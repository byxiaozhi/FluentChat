import React from 'react';
import { Route, Routes } from 'react-router';
import './App.scss';
import NavigationView from './component/NavigationVew';
import IndexPage from './container/IndexPage';
import LoginPage from './container/LoginPage';
import SignupPage from './container/SignupPage';
import UserManager from './container/UserManager';
import { useAppSelector } from './service/store';
import { isAdmin, isCollector, isUploader } from './utility/auto';

const App: React.FC = () => {
  const user = useAppSelector(e => e.user);

  const navPages: IPageList = [
    { title: '用户管理', path: '/UserManager', element: <UserManager />, auth: isAdmin },
  ]

  const otherPages: IPageList = [
    { title: '登录', path: '/login', element: <LoginPage /> },
    { title: '注册', path: '/signup', element: <SignupPage /> },
  ]

  return (
    <NavigationView pages={navPages}>
      <Routes>
        {[...navPages, ...otherPages].filter(e => !e.auth || e.auth(user?.role)).map(e =>
          <Route key={e.path} path={e.path} element={e.element} />
        )}
        <Route path='/' element={<IndexPage/>} />
      </Routes>
    </NavigationView>
  );
}

export default App;
