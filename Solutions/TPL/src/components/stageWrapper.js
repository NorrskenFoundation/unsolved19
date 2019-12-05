import React from "react";
import styled from "styled-components";

const StageWrapperMargin = styled.div`
  > button {
    margin-top: 1rem;
    margin-right: 0.5rem;
  }
`;

const Line = styled.div`
  border: 1px dashed #ddd;
  width: 1px;
  background: none;
  height: 100px;
  margin: 2rem auto;
`;

const StageWrapper = ({ children }) => (
  <StageWrapperMargin>
    {children}
    <Line />
  </StageWrapperMargin>
);

export default StageWrapper;
