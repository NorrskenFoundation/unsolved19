import React from 'react';
import styled from 'styled-components';

const RoundButton = styled.div`
  position: fixed;
  bottom: 2rem;
  right: 2rem;
  padding: 0.5rem 1.5rem;
  background: white;
  color: #191919;
  border-radius: 100%;

  font-size: 42px;
`;

const AddButton: React.FC<{ onClick: any }> = ({ onClick }) => {
  return <RoundButton onClick={onClick}>+</RoundButton>;
};

export default AddButton;
