import React, { useState } from "react";
import styled from "styled-components";
import { Provider } from "../../utils";
import Loader from "./Loader";
import { Button } from "@material-ui/core";
interface ProviderItemProps {
  provider: Provider;
}

const ProviderWrapper = styled.div`
  padding: 1rem;
  margin: 1rem;
  box-shadow: 0px 0px 5px 0px rgba(0, 0, 0, 0.4);
  display: flex;
  background: white;
  border-radius: 4px;

  &:hover {
    cursor: pointer;
    box-shadow: 0px 0px 25px 0px rgba(0, 0, 0, 0.4);
  }
`;
const ProviderStatus = styled.div`
  justify-self: flex-end;
  justify-content: center;
  align-items: center;
  display: flex;
`;
const ProviderLogo = styled.img`
  height: 64px;
`;
const ProviderLogoWrapper = styled.div`
  flex: auto;
  display: flex;
  justify-content: flex-start;
`;

const Connected = styled.div`
  color: #1b1b1b;
  font-size: 12px;
  font-weight: bold;
  text-align: right;
`;
const ConntectedSubtitle = styled.div`
  font-weight: normal;
`;

const ConnectedUser = ({
  connected,
  onClick,
  id
}: {
  onClick: any;
  connected: boolean;
  id: string;
}) => {
  return !connected ? (
    <Button onClick={onClick} id={id}>
      Connect
    </Button>
  ) : (
    <Connected>
      <ConntectedSubtitle>Connected with:</ConntectedSubtitle>
      Anna Andersson
    </Connected>
  );
};

const ProviderItem: React.FC<ProviderItemProps> = ({ provider }) => {
  const clickButton = () => {
    const btn = document.getElementById(provider.id);

    if (btn) {
      btn.click();
    }
  };

  const [fakeLoading, setFakeLoading] = useState(false);
  const [connected, setConnected] = useState(false);
  return (
    <ProviderWrapper onClick={clickButton}>
      <ProviderLogoWrapper>
        <ProviderLogo src={provider.logo} />
      </ProviderLogoWrapper>
      <ProviderStatus>
        {fakeLoading ? <Loader></Loader> : null}
        {fakeLoading ? null : (
          <ConnectedUser
            onClick={() => {
              setFakeLoading(true);
              setTimeout(() => {
                setConnected(true);
                setFakeLoading(false);
              }, 2000);
            }}
            id={provider.id}
            connected={connected}
          />
        )}
      </ProviderStatus>
    </ProviderWrapper>
  );
};

export default ProviderItem;
